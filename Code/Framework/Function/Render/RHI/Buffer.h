#pragma once
#include <vulkan/vulkan.h>
#include "Framework/Function/Render/RenderDefines.h"
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/GPUResource.h"

namespace Rosefinch
{

    // per platform/API implementatin of BufferAddressInfo
    struct BufferAddressInfoInternal;

    // A structure representing buffer addressing information used to bind buffer resources
    // to the GPU. Private implementations can be found under each API/Platform folder
    struct BufferAddressInfo
    {
        uint64_t addressInfosize[4]; // memory placeholder
        const BufferAddressInfoInternal* GetImpl() const { return (const BufferAddressInfoInternal*)addressInfosize; }
    };

    // Per platform/API implementation of BufferCopyDesc
    struct BufferCopyDescInternal;

    // A structure representing buffer copy job description used to copy buffer resources
    // on the GPU. Private implementations can be found under each API/Platform folder
    struct BufferCopyDesc
    {
        BufferCopyDesc() = default;
        BufferCopyDesc(const GPUResource* pSrc, const GPUResource* pDst);

        uint64_t bufferCopyDescMem[6];
        BufferCopyDescInternal* GetImpl() { return (BufferCopyDescInternal*)bufferCopyDescMem; }
        const BufferCopyDescInternal* GetImpl() const { return (const BufferCopyDescInternal*)bufferCopyDescMem; }
    };

    enum class BufferType
    {
        Vertex,                // vertex buffer
        Index,                 // index buffer
        Constant,              // constant buffer
        AccelerationStructure, // acceleration structure
        Data                   // generatic data buffer
    };

    struct BufferDesc
    {
        BufferType Type = BufferType::Vertex;
        ResourceFlags Flags = ResourceFlags::None;
        uint32_t Size = 0;      // the size of the buffer in bytes
        uint32_t Alignment = 0; // the required aligment of the buffer
        union
        {
            uint32_t Stride = 0;   // the stride of the buffer or
            ResourceFormat Format; // the format of the buffer (when usign an index buffer)
        };

        std::string Name = ""; // the name to assign to the created buffer resource

        static inline BufferDesc Vertex(const char* name, uint32_t size, uint32_t stride, uint32_t aligment = 0, ResourceFlags flags = ResourceFlags::None)
        {
            BufferDesc desc;
            desc.Type = BufferType::Vertex;
            desc.Flags = flags;
            desc.Size = size;
            desc.Alignment = aligment;
            desc.Stride = stride;
            desc.Name = name;

            return desc;
        }

        static inline BufferDesc Index(const char* name, uint32_t size, ResourceFormat format, uint32_t alignment = 0, ResourceFlags flags = ResourceFlags::None)
        {
            BufferDesc desc;
            desc.Type = BufferType::Index;
            desc.Flags = flags;
            desc.Size = size;
            desc.Alignment = alignment;
            desc.Format = format;
            desc.Name = name;

            return desc;
        }

        static inline BufferDesc Constant(const char* name, uint32_t size, uint32_t stride, uint32_t alignment = 0, ResourceFlags flags = ResourceFlags::None)
        {
            BufferDesc desc;
            desc.Type = BufferType::Constant;
            desc.Flags = flags;
            desc.Size = size;
            desc.Alignment = alignment;
            desc.Stride = stride;
            desc.Name = name;

            return desc;
        }

        static inline BufferDesc Data(const char* name, uint32_t size, uint32_t stride, uint32_t alignment = 0, ResourceFlags flags = ResourceFlags::None)
        {
            BufferDesc desc;
            desc.Type = BufferType::Data;
            desc.Flags = flags;
            desc.Size = size;
            desc.Alignment = alignment;
            desc.Stride = stride;
            desc.Name = name;

            return desc;
        }

        static inline BufferDesc AccelerationStructure(const char* name, uint32_t size, uint32_t stride, uint32_t alignment = 0, ResourceFlags flags = ResourceFlags::None)
        {
            BufferDesc desc;
            desc.Type = BufferType::AccelerationStructure;
            desc.Flags = flags;
            desc.Size = size;
            desc.Alignment = alignment;
            desc.Stride = stride;
            desc.Name = name;

            return desc;
        }
    };

    class UploadContext;

    class Buffer
    {
    public:
        // Function signature for buffer ResizeFunction (when needed).
        typedef void (*ResizeFunction)(BufferDesc&, uint32_t, uint32_t, uint32_t, uint32_t);

        virtual ~Buffer();

        static Buffer* CreateBufferResource(const BufferDesc* pDesc, ResourceState initialState, ResizeFunction fn = nullptr);

        const BufferDesc& GetDesc() const { return m_BufferDesc; }

        const GPUResource* GetResource() const { return m_pResource; }

        // Copy callback used when loading buffer data. Implemented internally per api/platform.
        virtual void CopyData(const void* pData, size_t size) = 0;
        virtual void CopyData(const void* pData, size_t size, UploadContext* pUploadCtx, ResourceState postCopyState) = 0;

        // Gets the buffer's BufferAddressInfo for resource binding. Implemented internally per api/platform.
        virtual BufferAddressInfo GetAddressInfo() const = 0;

        void OnRenderingResolutionResize(uint32_t outputWidth, uint32_t outputHeight, uint32_t renderingWidth, uint32_t renderingHeight);

    private:
        NO_COPY(Buffer)
        NO_MOVE(Buffer)

    protected:
        Buffer(const BufferDesc* pDesc, ResizeFunction fn);
        virtual void Recreate() = 0;

        Buffer() = delete;

        BufferDesc m_BufferDesc = {};
        GPUResource* m_pResource = nullptr;
        ResizeFunction m_ResizeFn = nullptr;
    };
}