#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"

namespace Rosefinch
{

    class GPUResource;
    class Texture;
    class Buffer;
    class Sampler;

    // Per platform/api implementation of ResourceViewInfo
    struct ResourceViewInfoInternal;

    /**
     * A structure representing resource view information used to bind resources
     * to the GPU. Private implementations can be found under each api/platform folder
     */
    struct ResourceViewInfo
    {
        uint64_t resourceViewSize[6]; // Memory placeholder
        const ResourceViewInfoInternal* GetImpl() const { return (ResourceViewInfoInternal*)resourceViewSize; }
    };

    struct TextureDesc;
    struct BufferDesc;

    /**
     * @class ResourceView
     *
     * The api/platform-agnostic representation of the resource view
     */
    class ResourceView
    {
    public:
        /**
         * ResourceView instance creation function. Implemented per api/platform to return
         * the internal resoruce type
         */
        static ResourceView* CreateResourceView(ResourceViewHeapType type, uint32_t count, void* pInitParams);

        virtual ~ResourceView() = default;

        const uint32_t GetCount() const { return m_Count; }

        /**
         * Return the ResourceViewInfo
         */
        virtual const ResourceViewInfo GetViewInfo(uint32_t index = 0) const = 0;

        /**
         * Bind a texture resource view
         */
        virtual void BindTextureResource(const GPUResource* pResource, const TextureDesc& texDesc, ResourceViewType type, ViewDimension dimension, int32_t mip, int32_t arraySize, int32_t firstArraySlice, uint32_t index = 0) = 0;

        /**
         * Bind a buffer resource view
         */
        virtual void BindBufferResource(const GPUResource* pResource, const BufferDesc& bufferDesc, ResourceViewType type, uint32_t firstElement, uint32_t numElements, uint32_t index = 0) = 0;

        /**
         * Bind a sampler resource view
         */
        virtual void BindSamplerResource(const Sampler* pSampler, uint32_t index = 0) = 0;

    private:
        NO_COPY(ResourceView)
        NO_MOVE(ResourceView)

    protected:
        ResourceView(ResourceViewHeapType type, uint32_t count);
        ResourceView() = delete;

        ResourceViewHeapType m_Type = ResourceViewHeapType::GPUResourceView;
        uint32_t m_Count = 0;
    };
}