#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"

namespace Rosefinch
{
    class Buffer;
    struct BufferDesc;
    class GPUResource;
    class Texture;
    struct TextureDesc;

    /**
     * @class DynamicResourcePool
     *
     * The dynamic resource pool is the allocation construct used to back all resource creation
     */
    class DynamicResourcePool
    {
    public:
        DynamicResourcePool();

        virtual ~DynamicResourcePool();

        /**
         * Callback when the rendering resolution changed. Will call all resource resize function callbacks
         * and recreate/rebind all resources automatically in the background
         */
        void OnResolutionChanged(const ResolutionInfo& resInfo);

        /**
         * Destroy a GPU resource
         */
        void DestroyResource(const GPUResource* pResource);

        /**
         * Fetch a Texture resoure by name. Will assert when called on the main thread while
         * the Framework is running as it use a map construct for lookup.
         */
        const Texture* GetTexture(const char* name);

        /**
         * Fetch a Buffer resource by name.
        */
        const Buffer* GetBuffer(const char* name);

        typedef void (*TextureResizeFunction)(TextureDesc&, uint32_t, uint32_t, uint32_t, uint32_t);
        typedef void (*BufferResizeFunction)(BufferDesc&, uint32_t, uint32_t, uint32_t, uint32_t);

        /**
         * Create a Texture resource. Will create the resource is the requested state.
        */
        const Texture* CreateTexture(const TextureDesc* pDesc, ResourceState initialState, TextureResizeFunction fn = nullptr);
    
        /**
         * Create a Texture resource for rendering. Will automatically and AllowRenderTarget/AllowDepthTarget
         * resource flag based on the resource type
        */
        const Texture* CreateRenderTexture(const TextureDesc* pDesc, TextureResizeFunction fn = nullptr);
    
        /**
         * Create a Buffer resource. Will create the resource is the requested state.
        */
        const Buffer* CreateBuffer(const BufferDesc* pDesc, ResourceState initialState, BufferResizeFunction fn = nullptr);
    
    private:
        std::vector<std::pair<std::string, Texture*>> m_Textures;
        std::vector<std::pair<std::string, Buffer*>> m_Buffers;
        std::vector<Texture*> m_ResizableTextures;
        std::vector<Buffer*> m_ResizableBuffers;
        std::mutex m_CriticalSection;
    };
} // namespace Rosefinch