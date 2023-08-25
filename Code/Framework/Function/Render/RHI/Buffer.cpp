#include "Buffer.h"

namespace Rosefinch
{
    namespace RHI
    {
        Buffer::Buffer(const BufferDesc *pDesc, ResizeFunction fn) : m_BufferDesc(*pDesc),
                                                                     m_ResizeFn(fn)
        {
        }

        Buffer::~Buffer()
        {
            delete m_pResource;
        }

        void Buffer::OnRenderingResolutionResize(uint32_t outputWidth, uint32_t outputHeight, uint32_t renderingWidth, uint32_t renderingHeight)
        {
            if (m_ResizeFn == nullptr)
            {
                LOG_CRITICAL("there is no method to resize the buffer");
                return;
            }
            m_ResizeFn(m_BufferDesc, outputWidth, outputHeight, renderingWidth, renderingHeight);

            Recreate();
        }
    }
}