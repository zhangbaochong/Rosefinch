#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"

namespace Rosefinch
{
    class CommandList;
    class GPUResource;

    /**
     * A structure representing an allocation block used to upload CPU-side memory to
     * a GPU resource
     */
    struct AllocationBlock
    {
        uint8_t* pDataBegin = nullptr; // The beginning of the allocation data
        uint8_t* pDataEnd = nullptr;   // The end of the allocation data
        size_t Size = 0;               // The size of the allocation
    };

    /**
     * A structure representing data transfer information. Is backed by an allocation block
     */
    struct TransferInfo
    {
        uint8_t* DataPtr(uint32_t sliceID) { return pSliceDataBegin[sliceID]; }

    private:
        friend class UploadHeap;
        AllocationBlock AllocationInfo;         // The backing allocation
        std::vector<uint8_t*> pSliceDataBegin; // The data pointer for each slice of data in the block
    };

    // Per platform/api implementation of UploadHeap
    class UploadHeapInternal;

    /**
     * @class UploadHeap
     *
     * The api/platform-agnostic representation of the upload heap
    */
    class UploadHeap
    {
    public:
        /**
         * UploadHeap instance creation function. Implemented per api/platform to return the
         * correct internal resource type
        */
        static UploadHeap* CreateUploadHeap();

        virtual ~UploadHeap();

        /**
         * Initialize the allocation block
        */
        void InitAllocationBlocks();

        /**
         * Return the UploadHeap's backing GPUResource
        */
        const GPUResource* GetResource() const { return m_pResource; }
        GPUResource* GetResource() { return m_pResource; }

        /**
         * Return the UploadHeap's base data pointer
        */
        uint8_t* BasePtr() { return m_pDataBegin; }

        /**
         * Return a TransferInfo instance setup to load a resource as requested
        */
        TransferInfo* BeginResourceTransfer(size_t sliceSize, uint64_t sliceAlignment, uint32_t numSlices);

        /**
         * End the resource transfer associated with the TransferInfo pointer
        */
        void EndResourceTransfer(TransferInfo* pTransferBlock);

        /**
         * Get the internal implementation for api/platform parameter accessors
        */
        virtual UploadHeapInternal* GetImpl() = 0;
        virtual const UploadHeapInternal* GetImpl() const = 0;

    private:
        NO_COPY(UploadHeap)
        NO_MOVE(UploadHeap)

    protected:
        UploadHeap() = default;
        GPUResource* m_pResource = nullptr;
        size_t m_Size = 0;

        uint8_t* m_pDataEnd = nullptr;      // Ending position of upload heap
        uint8_t* m_pDataBegin = nullptr;    // Starting position of upload heap

        std::vector<AllocationBlock> m_AvailableAllocations;
        std::vector<TransferInfo*> m_ActiveTransfers;
        std::mutex m_AllocationMutex;
        std::condition_variable m_AllocationCV;
    };
}