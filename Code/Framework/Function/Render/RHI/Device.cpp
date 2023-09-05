#include "Device.h"
#include "Framework/Function/Render/RHI/CommandList.h"

namespace Rosefinch
{
    Device::Device()
    {

    }

    Device::~Device()
    {

    }

    void Device::FlushAllCommandQueues()
    {
        FlushQueue(CommandQueue::Graphics);
        FlushQueue(CommandQueue::Compute);
        FlushQueue(CommandQueue::Copy);
    }

    CommandList* Device::BeginFrame()
    {
        m_pActiveCommandList = CreateCommandList("BeginFrameGraphicsCmdList", CommandQueue::Graphics);

        // for vulkan, no need to set resource view heaps

        return m_pActiveCommandList;
    }

    void Device::EndFrame()
    {
        CloseCmdList(m_pActiveCommandList);

        // Execute all submission command lists (only 1 for now)
        std::vector<CommandList*> cmdLists;
        cmdLists.push_back(std::move(m_pActiveCommandList));
        uint64_t signalValue = ExecuteCommandLists(cmdLists, CommandQueue::Graphics, true);

        // Asynchronously delete the active command list in the background once it's cleared the graphic queue
        GPUExecutionPacket* pInflightPacket = new GPUExecutionPacket(cmdLists, signalValue);
        // TODO add below
        // GetTaskManager()->AddTask(Task(std::bind(&Device::DeleteCommandListAsync, this, std::placeholders::_1), reinterpret_cast<void*>(pInflightPacket)));

        m_pActiveCommandList = nullptr;
    }

    void Device::DeleteCommandListAsync(void* pInFlightGPUInfo)
    {
        GPUExecutionPacket* pInflightPacket = static_cast<GPUExecutionPacket*>(pInFlightGPUInfo);

        // Wait until the command lists are processed
        WaitOnQueue(pInflightPacket->CompletionID, CommandQueue::Graphics);

        // Delete them to release the allocators
        for (auto cmdListIter = pInflightPacket->CmdLists.begin(); cmdListIter != pInflightPacket->CmdLists.end(); ++cmdListIter)
        {
            delete* cmdListIter;
        }

        pInflightPacket->CmdLists.clear();
        delete pInflightPacket;
    }
}