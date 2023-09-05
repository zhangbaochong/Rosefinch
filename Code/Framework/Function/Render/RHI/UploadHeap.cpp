#include "UploadHeap.h"
#include "Framework/Function/Render/RHI/GPUResource.h"

#include <chrono>
#include <thread>

namespace Rosefinch
{
    UploadHeap::~UploadHeap()
    {
        delete m_pResource;
    }

    void UploadHeap::InitAllocationBlocks()
    {
        // Only one block at the begining
        AllocationBlock allocationInfo;
        allocationInfo.pDataBegin = m_pDataBegin;
        allocationInfo.pDataEnd = m_pDataEnd;
        allocationInfo.Size = ((uint64_t)m_pDataEnd) - ((uint64_t)m_pDataBegin);

        m_AvailableAllocations.push_back(allocationInfo);
    }

    TransferInfo* UploadHeap::BeginResourceTransfer(size_t sliceSize, uint64_t sliceAlignment, uint32_t numSlices)
    {
        // Before we try to make any modifications, see how much mem we need and check if there is enough avaliable
        size_t requiredSize = AlignUp(sliceSize, sliceAlignment) * numSlices;
        RosefinchAssert(ASSERT_CRITICAL, requiredSize < m_Size, "Resource will not fit into upload heap, Please make it bigger");

        // Spin here until we can get the size we need (might have to wait for other jobs to finish up)
        uint8_t* pDataBegin = nullptr;
        uint8_t* pDataEnd = nullptr;

        TransferInfo* pTransferInfo = nullptr;
        bool logged = false;

        while (!pTransferInfo)
        {
            // Go through the list of allocation blocks and find one big enough to accommodate us
            {
                std::unique_lock<std::mutex> lock(m_AllocationMutex);
                std::vector<AllocationBlock>::iterator iter = m_AvailableAllocations.begin();
                while (iter != m_AvailableAllocations.end())
                {
                    if ((*iter).Size > requiredSize)
                    {
                        // Figure out the begin, aligned begin, and end for the memory we want to use
                        pDataBegin = (*iter).pDataBegin;
                        uint8_t* pAlignedBegin = reinterpret_cast<uint8_t*>(AlignUp(reinterpret_cast<size_t>(pDataBegin), static_cast<size_t>(sliceAlignment)));
                        pDataEnd = reinterpret_cast<uint8_t*>(reinterpret_cast<size_t>(pAlignedBegin) + requiredSize);

                        // Modify the existing block
                        (*iter).pDataBegin = pDataEnd;
                        (*iter).Size = ((uint64_t)(*iter).pDataEnd) - ((uint64_t)(*iter).pDataBegin);

                        // Create out transfer block
                        m_ActiveTransfers.push_back(new TransferInfo());
                        pTransferInfo = m_ActiveTransfers.back();
                        break;
                    }

                    ++iter;
                }

                // If we got here, could't find a blocking big enough. Sleep a bit and try again
                if (!pTransferInfo)
                {
                    if (!logged)
                    {
                        logged = true; // Don't spam the output for the same resource
                    }
                    m_AllocationCV.wait(lock);
                }
            }
        }

        // Got our memory, setup the transfer information, the slice pointers and fetch a command list to record the work
        pTransferInfo->AllocationInfo.pDataBegin = pDataBegin;
        pTransferInfo->AllocationInfo.pDataEnd = pDataEnd;
        pTransferInfo->AllocationInfo.Size = ((uint64_t)pTransferInfo->AllocationInfo.pDataEnd) - ((uint64_t)pTransferInfo->AllocationInfo.pDataBegin);

        uint8_t* pSliceStart = pDataBegin;
        for (uint32_t i = 0; i < numSlices; ++i)
        {
            pSliceStart = reinterpret_cast<uint8_t*>(AlignUp(reinterpret_cast<size_t>(pSliceStart), static_cast<size_t>(sliceAlignment)));
            pTransferInfo->pSliceDataBegin.push_back(pSliceStart);
            pSliceStart += (sliceSize);
        }
        return pTransferInfo;
    }

    void UploadHeap::EndResourceTransfer(TransferInfo* pTransferBlock)
    {
        // Lock to avoid data collisions
        {
            std::unique_lock<std::mutex> lock(m_AllocationMutex);

            // Return the allocation block to the pool (will join memory to an adjacent block where possible)
            std::vector<AllocationBlock>::iterator iter = m_AvailableAllocations.begin();

            // First find the right spot to insert it (ordered)
            for (; iter != m_AvailableAllocations.end(); ++iter)
            {
                if ((*iter).pDataBegin >= pTransferBlock->AllocationInfo.pDataEnd)
                {
                    break;
                }
            }
            iter = m_AvailableAllocations.insert(iter, pTransferBlock->AllocationInfo);

            // Now merge adjacent blocks together to free up large blocks
            for (size_t index = m_AvailableAllocations.size() - 1; index >= 1; --index)
            {
                // Check if they are joinable
                if (m_AvailableAllocations[index].pDataBegin == m_AvailableAllocations[index - 1].pDataEnd)
                {
                    // Merge them
                    m_AvailableAllocations[index - 1].pDataEnd = m_AvailableAllocations[index].pDataEnd;
                    m_AvailableAllocations[index - 1].Size += m_AvailableAllocations[index].Size;

                    // Remove the previous element
                    m_AvailableAllocations.erase(std::next(m_AvailableAllocations.begin(), index));
                }
            }

            // Find and destroy this active transfer to clean everything up
            std::vector<TransferInfo*>::iterator transferIter = m_ActiveTransfers.begin();
            while (transferIter != m_ActiveTransfers.end())
            {
                if (*transferIter == pTransferBlock)
                {
                    delete pTransferBlock;
                    m_ActiveTransfers.erase(transferIter);
                    break;
                }

                ++transferIter;
            }

            // Signal any pending allocations
            m_AllocationCV.notify_one();
        }
    }
}