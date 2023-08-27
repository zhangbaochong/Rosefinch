#include "CommandList_Vulkan.h"
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    void SetAllResourceViewHeaps(CommandList* pCmdList, ResourceViewAllocator* pAllocator)
    {
        // Do nothing on vulkan
    }

    void CloseCmdList(CommandList* pCmdList)
    {
        //VkResult res = vkEndCommandBuffer(pCmdList->GetImpl()->VKCmdBuffer());
        //RosefinchAssert(AssertLevel::Error, res == VK_SUCCESS, "Failed to end recording into a command buffer");
    }
}