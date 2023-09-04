#include "DynamicBufferPool.h"
#include "Framework/Function/GlobalContext.h"

namespace Rosefinch
{
    DynamicBufferPool::DynamicBufferPool()
    {
        const RenderConfig *pConfig = g_RuntimeGlobalContext.m_RenderSystem->GetConfig();
        m_TotalSize = AlignUp<uint32_t>(static_cast<uint32_t>(pConfig->DynamicBufferPoolSize), 256u);

        // Create the backing ring buffer
        m_RingBuffer.Create(pConfig->BackBufferCount, m_TotalSize);
    }

    DynamicBufferPool::~DynamicBufferPool()
    {
        // Destroy the backing ring buffer
        m_RingBuffer.Destroy();

        delete m_pResource;
    }

    void DynamicBufferPool::BeginFrame()
    {
        m_RingBuffer.BeginFrame();
    }
} // namespace Rosefinch