#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RenderDefines.h"

namespace Rosefinch
{
    class ResourceViewAllocator;

    class CommandList
    {
    public:
        virtual ~CommandList() = default;

    private:
        NO_COPY(CommandList)
        NO_MOVE(CommandList)
    
    protected:
        CommandList(CommandQueue queueType);
    };
    /**
     * Set all resource view heaps to the CommandList.
    */
    void SetAllResourceViewHeaps(CommandList* pCmdList, ResourceViewAllocator* pAllocator = nullptr);

    /**
     * Closes the CommandList.
    */
    void CloseCmdList(CommandList* pCmdList);
}
