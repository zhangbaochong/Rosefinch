#include "Buffer.h"

namespace Rosefinch
{

    Buffer::Buffer(const BufferDesc* pDesc, ResizeFunction fn) : m_BufferDesc(*pDesc),
        m_ResizeFn(fn)
    {
    }

    Buffer::~Buffer()
    {
        delete m_pResource;
    }

    void Buffer::OnRenderingResolutionResize(uint32_t outputWidth, uint32_t outputHeight, uint32_t renderingWidth, uint32_t renderingHeight)
    {
        RosefinchAssert(AssertLevel::ASSERT_CRITICAL, m_ResizeFn != nullptr, "there is no method to resize the buffer");

        m_ResizeFn(m_BufferDesc, outputWidth, outputHeight, renderingWidth, renderingHeight);

        Recreate();
    }
}
