#pragma once

#include "Framework/Core/Base.h"
#include "Framework/Core/Ring.h"
#include "Framework/Function/Render/RenderDefines.h"

namespace Rosefinch
{
    struct BufferAddressInfo;
    class GPUResource;

    /**
     * @class DynamicBufferPool
     *
     * The api/platform-agnostic representation of a dynamic buffer pool
     */
    class DynamicBufferPool
    {
    public:
        /**
         * DynamicBufferPool instance creation function. Implemented per api/platform to return
         * the correct internal resource type
         */
        static DynamicBufferPool* CreateDynamicBufferPool();

        virtual ~DynamicBufferPool();

        /**
         * Prepare the buffer pool for usage for the frame (cycle the ring buffer)
         */
        void BeginFrame();

        /**
         * Allocate a temporary constant buffer and initialize it with the provided memory.
         * Return the BufferAddressInfo for the buffer.
         */
        virtual BufferAddressInfo AllocConstantBuffer(uint32_t size, const void* pInitData) = 0;

        /**
         * Allocate a temporary vertex buffer and map the provided pointer to the backing memory.
         * Return the BufferAddressInfo for the buffer.
         */
        virtual BufferAddressInfo AllocVertexBuffer(uint32_t vertexCount, uint32_t vertexStride, void** pBuffer) = 0;

        /**
         * Allocate a temporary index buffer and map the provided pointer to the backing memory.
         * Return the BufferAddressInfo for the buffer.
         */
        virtual BufferAddressInfo AllocIndexBuffer(uint32_t indexCount, uint32_t indexStride, void** pBuffer) = 0;

        /**
         * Get a constant pointer to the buffer pool's underlaying GPUResource.
        */
        const GPUResource* GetResource() const { return m_pResource; }

    private:
        NO_COPY(DynamicBufferPool)
        NO_MOVE(DynamicBufferPool)

    protected:
        // Special case for swap chains
        DynamicBufferPool();

        uint32_t m_TotalSize = 0;
        RingWithTabs m_RingBuffer = {};
        uint8_t* m_pData = nullptr;

        // Backing resource
        GPUResource* m_pResource = nullptr;
    };

} // namespace Rosefinch