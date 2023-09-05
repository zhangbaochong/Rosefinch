#include "Texture.h"
#include "Framework/Function/Render/RHI/GPUResource.h"

namespace Rosefinch
{
    Texture* Texture::CreateTexture(const TextureDesc* pDesc, ResourceState initialState, ResizeFunction fn)
    {
        return new Texture(pDesc, initialState, fn);
    }

    Texture* Texture::CreateSwapChainTexture(const TextureDesc* pDesc, GPUResource* pResource)
    {
        return new Texture(pDesc, pResource);
    }

    Texture* Texture::CreateContentTexture(const TextureDesc* pDesc)
    {
        return new Texture(pDesc, ResourceState::CopyDest, nullptr);
    }

    Texture::~Texture()
    {
        delete m_pResource;
    }

    void Texture::OnRenderingResolutionResize(uint32_t outputWidth, uint32_t outputHeight, uint32_t renderingWidth, uint32_t renderingHeight)
    {
        RosefinchAssert(ASSERT_CRITICAL, m_ResizeFn != nullptr, "There's no method to resize the texture");

        m_ResizeFn(m_TextureDesc, outputWidth, outputHeight, renderingWidth, renderingHeight);

        Recreate();
    }

    SwapChainRenderTarget::SwapChainRenderTarget(const TextureDesc* pDesc, std::vector<GPUResource*>& resources)
        : Texture(pDesc, resources[0])
    {
        // initialize resources pointers
        for (int i = 1; i < resources.size(); ++i)
        {
            m_AdditionalTextures.push_back(Texture::CreateSwapChainTexture(pDesc, resources[i]));
        }

        // setup all texture pointers and resource ownership
        Texture::GetResource()->SetOwner(this);
        m_TextureResources.push_back(this);
        for (int i = 0; i < m_AdditionalTextures.size(); ++i)
        {
            m_TextureResources.push_back(m_AdditionalTextures[i]);
            m_AdditionalTextures[i]->GetResource()->SetOwner(m_TextureResources.back());
        }
    }

    SwapChainRenderTarget::~SwapChainRenderTarget()
    {
        if (m_AdditionalTextures.size())
        {
            ClearResources();
        }
    }

    void SwapChainRenderTarget::SetCurrentBackBufferIndex(uint32_t index)
    {
        RosefinchAssert(ASSERT_CRITICAL, index < m_TextureResources.size(), "Backbuffer index out of range");
        m_CurrentBackBuffer = index;
    }

    void SwapChainRenderTarget::ClearResources()
    {
        delete m_pResource;
        m_pResource = nullptr;

        for (auto texIter = m_AdditionalTextures.begin(); texIter != m_AdditionalTextures.end(); ++texIter)
        {
            delete (*texIter);
        }
        m_AdditionalTextures.clear();
        m_TextureResources.clear();
    }

    void SwapChainRenderTarget::Update(const TextureDesc* pDesc, std::vector<GPUResource*>& resources)
    {
        // Update all backing resources
        m_TextureDesc = *pDesc;

        // Copy the new main resource
        int resourceIndex = 0;
        m_pResource = resources[resourceIndex++];

        // Initialize resources pointers
        for (int i = 1; i < resources.size(); ++i)
        {
            m_AdditionalTextures.push_back(Texture::CreateSwapChainTexture(pDesc, resources[i]));
        }

        // Setup all texture pointers
        m_TextureResources.push_back(this);
        for (int i = 0; i < m_AdditionalTextures.size(); ++i)
        {
            m_TextureResources.push_back(m_AdditionalTextures[i]);
        }
    }
}