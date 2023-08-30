#include "ResourceViewAllocator.h"
#include "Framework/Function/GlobalContext.h"

namespace Rosefinch
{
    ResourceViewAllocator::ResourceViewAllocator()
    {
        const RenderConfig *pConfig = g_RuntimeGlobalContext.m_RenderSystem->GetConfig();
        m_NumViews[static_cast<size_t>(ResourceViewHeapType::GPUResourceView)] = pConfig->GPUResourceViewCount;
        m_NumViews[static_cast<size_t>(ResourceViewHeapType::CPUResourceView)] = pConfig->CPUResourceViewCount;
        m_NumViews[static_cast<size_t>(ResourceViewHeapType::CPURenderView)] = pConfig->CPURenderViewCount;
        m_NumViews[static_cast<size_t>(ResourceViewHeapType::CPUDepthView)] = pConfig->CPUDepthViewCount;
        m_NumViews[static_cast<size_t>(ResourceViewHeapType::GPUSamplerView)] = pConfig->GPUSamplerViewCount;
    }
}