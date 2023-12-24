#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"

namespace Rosefinch
{
    // A structure representing a texture description
    struct TextureDesc
    {
        ResourceFormat Format = ResourceFormat::Unknown;
        ResourceFlags Flags = ResourceFlags::None;
        uint32_t Width = 0;
        uint32_t Height = 0;
        TextureDimension Dimension = TextureDimension::Unknown;
        uint32_t DepthOrArraySize = 0;
        uint32_t MipLevels = 0;
        std::string Name = "";

        // A convenience function to create a texture description for 1D textures
        static inline TextureDesc Tex1D(const char* name, ResourceFormat format, uint32_t width, uint32_t arraySize = 1, uint32_t mipLevels = 0, ResourceFlags flags = ResourceFlags::None)
        {
            TextureDesc desc;
            desc.Format = format;
            desc.Flags = flags;
            desc.Width = width;
            desc.Height = 1;
            desc.Dimension = TextureDimension::Texture1D;
            desc.DepthOrArraySize = arraySize;
            desc.MipLevels = mipLevels;
            desc.Name = name;

            return desc;
        }

        // A convenience function to create a texture description for 2D textures
        static inline TextureDesc Tex2D(const char* name, ResourceFormat format, uint32_t width, uint32_t height, uint32_t arraySize = 1, uint32_t mipLevels = 0, ResourceFlags flags = ResourceFlags::None)
        {
            TextureDesc desc;
            desc.Format = format;
            desc.Flags = flags;
            desc.Width = width;
            desc.Height = height;
            desc.Dimension = TextureDimension::Texture2D;
            desc.DepthOrArraySize = arraySize;
            desc.MipLevels = mipLevels;
            desc.Name = name;

            return desc;
        }

        // A convenience function to create a texture description for 3D textures
        static inline TextureDesc Tex3D(const char* name, ResourceFormat format, uint32_t width, uint32_t height, uint32_t depth = 1, uint32_t mipLevels = 0, ResourceFlags flags = ResourceFlags::None)
        {
            TextureDesc desc;
            desc.Format = format;
            desc.Flags = flags;
            desc.Width = width;
            desc.Height = height;
            desc.Dimension = TextureDimension::Texture3D;
            desc.DepthOrArraySize = depth;
            desc.MipLevels = mipLevels;
            desc.Name = name;

            return desc;
        }

        // A convenience function to create a texture description for cube textures
        static inline TextureDesc TexCube(const char* name, ResourceFormat format, uint32_t width, uint32_t height, uint32_t depth = 1, uint32_t mipLevels = 0, ResourceFlags flags = ResourceFlags::None)
        {
            TextureDesc desc;
            desc.Format = format;
            desc.Flags = flags;
            desc.Width = width;
            desc.Height = height;
            desc.Dimension = TextureDimension::CubeMap;
            desc.DepthOrArraySize = 6 * depth;
            desc.MipLevels = mipLevels;
            desc.Name = name;

            return desc;
        }
    };

    class GPUResource;
    class TextureDataBlock;

    // Per platform/API implementation of Texture
    class TextureInternel;

    /**
     * @class Texture
     *
     * The api/platform-agnostic representation of a texture resource
     */
    class Texture
    {
    public:
        typedef void (*ResizeFunction)(TextureDesc&, uint32_t, uint32_t, uint32_t, uint32_t);

        /**
         * Texture instance creation function. Implemented per api/platform to return the correct
         * internal resource type
         */
        static Texture* CreateTexture(const TextureDesc* pDesc, ResourceState initialState, ResizeFunction fn = nullptr);

        /**
         * Texture instance creation function for swap chains. Implemented per api/platform to return
         * the correct internal resource type
         */
        static Texture* CreateSwapChainTexture(const TextureDesc* pDesc, GPUResource* pResource);

        /**
         * Texture instance creation function for loaded content. Implemented per api/platform to return
         * the correct internal resource type
         */
        static Texture* CreateContentTexture(const TextureDesc* pDesc);

        virtual ~Texture();

        ResourceFormat GetFormat() const { return m_TextureDesc.Format; }

        const TextureDesc& GetDesc() const { return m_TextureDesc; }

        /**
         * Return the texture's backing GPUResource
         */
        GPUResource* GetResource() { return m_pResource; }
        const GPUResource* GetResource() const { return m_pResource; }

        /**
         * Copy data form a texture data block into the texture resource. Used when loading content from file/memory
         */
        void CopyData(TextureDataBlock* pTextureDataBlock);

        /**
         * Return true if the resource is a swap chain. Used to isolate swapchain surfaces from
         * non-swap chain (specialization class exists per platform to overload this)
         */
        virtual bool IsSwapChain() const { return false; }

        /**
         * Callback invoked by OnResize event
         */
        void OnRenderingResolutionResize(uint32_t outputWidth, uint32_t outputHeight, uint32_t renderingWidth, uint32_t renderingHeight);

        TextureInternel* GetImpl() { return m_pImpl; }
        const TextureInternel* GetImpl() const { return m_pImpl; }

    private:
        NO_COPY(Texture)
        NO_MOVE(Texture)

    protected:
        Texture(const TextureDesc* pDesc, ResourceState initialState, ResizeFunction fn);
        Texture(const TextureDesc* pDesc, GPUResource* pResource);
        Texture() = delete;

        void Recreate();

        TextureDesc m_TextureDesc = {};
        GPUResource* m_pResource = nullptr;
        TextureInternel* m_pImpl = nullptr;
        ResizeFunction m_ResizeFn = nullptr;
    };

    /**
     * @class SwapChainRenderTarget
     *
     * The api/platform-agnostic representation of a swap chain render target resource
     */
    class SwapChainRenderTarget : public Texture
    {
    public:
        virtual ~SwapChainRenderTarget();

        /**
         * Return true to indicate the resouce is a swapchain
         */
        virtual bool IsSwapChain() const override { return true; }

        /**
         * Return the number of back buffers held by the resource
         */
        uint32_t GetBackBufferCount() const { return static_cast<uint32_t>(m_TextureResources.size()); }

        /**
         * Return the specified back buffer backing GPUResource
         */
        GPUResource* GetResource(uint32_t index) const { return m_TextureResources[index]->GetResource(); }

        /**
         * Return the current back buffer
         */
        GPUResource* GetCurrentResource() const { return m_TextureResources[m_CurrentBackBuffer]->GetResource(); }

    private:
        friend class SwapChain;
        friend class SwapChainInternel;
        SwapChainRenderTarget(const TextureDesc* pDesc, std::vector<GPUResource*>& resources);

        void SetCurrentBackBufferIndex(uint32_t index);
        void ClearResources();
        void Update(const TextureDesc* pDesc, std::vector<GPUResource*>& resources);

    private:
        uint32_t m_CurrentBackBuffer = 0;
        Texture* m_pCurrentTexture = nullptr;
        std::vector<Texture*> m_AdditionalTextures;
        std::vector<Texture*> m_TextureResources;
    };

    // Per aip/platform implementation of TextureCopyDesc
    struct TextureCopyDescInternel;

    /**
     * A structure representing texture copy job description used to copy texture resources
     * on the GPU. Private implementations can be found under each api/platform folder
     */
    struct TextureCopyDesc
    {
        TextureCopyDesc() = default;
        TextureCopyDesc(const GPUResource* pSrc, const GPUResource* pDst);

        uint64_t textureCopyDescMem[20]; // memory placeholder
        TextureCopyDescInternel* GetImpl() { return (TextureCopyDescInternel*)textureCopyDescMem; }
        const TextureCopyDescInternel* GetImpl() const { (const TextureCopyDescInternel*)textureCopyDescMem; }
    };
}