#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"
#include "Framework/Function/Render/RHI/ResourceView.h"
#include "Framework/Function/Render/Shaders/ShaderCommon.h"

#include <fstream>

namespace Rosefinch
{
    class SwapChainRenderTarget;

    // Per api/platform implementation of SwapChain
    class SwapChainInternel;

    /**
     * @class SwapChain
     *
     * The api/platform-agnostic representation of the swapchain object. Interface for all
     * presentation-related interfaces
    */
    class SwapChain
    {
    public:
        static const char* s_SwapChainRTName;

        /**
         * SwapChain instance creation function. Implemented per api/platform to return the
         * internal resource type
        */
        static SwapChain* CreateSwapChain();

        /**
         * Destruction.
        */
        virtual ~SwapChain();

        /**
         * Return the swap chain resource's format.
        */
        ResourceFormat GetSwapChainFormat() const { return m_SwapChainFormat; }

        /**
         * Return the configured backbuffer count for this run.
        */
        size_t GetBackBufferCount();

        /**
         * Return the current SwapChainRenderTarget.
        */
        SwapChainRenderTarget* GetBackBufferRT() { return m_pRenderTarget; }

        /**
         * Return the current back buffer's render target view ResourceViewInfo.
         */
        const ResourceViewInfo GetBackBufferRTV() const { return GetBackBufferRTV(m_CurrentBackBuffer); }

        /**
         * Return the specified back buffer's render target view ResourceViewInfo.
         */
        const ResourceViewInfo GetBackBufferRTV(uint8_t idx) const { return m_pSwapChainRTV->GetViewInfo(static_cast<uint32_t>(idx)); }

        /**
         * Return the current back buffer's index
        */
        uint8_t GetBackBufferIndex() const { return m_CurrentBackBuffer; }

        /**
         * Return the swap chain's configured DisplayMode
        */
        const DisplayMode GetSwapChainDisplayMode() const { return  m_CurrentDisplayMode; }

        /**
         * Return the swap chain's configured HDRMetadata.
        */
        const HDRMetadata& GetHDRMetaData() const { return m_HDRMetadata; }

        /**
         * Callback invoked while processing OnResize events.
        */
        virtual void OnResize(uint32_t width, uint32_t height) = 0;

        /**
         * Waits until the last submitted swap chain has finished presenting. Only waits when we run too far ahead.
        */
        virtual void WaitForSwapChain() = 0;

        /**
         * Execute device presentation of the swapchain.
        */
        virtual void Present() = 0;

        /**
         * Create a screenshot of the current swapchain.
        */
        virtual void DumpSwapChainToFile(std::experimental::filesystem::path filePath) = 0;

        /**
         * Verify if requested display mode can be supported.
        */
        DisplayMode CheckAndGetDisplayModeRequested(DisplayMode displayMode);

        /**
         * Prepare the HDRMetadat based on the seleted display mode for the run.
        */
        void PopulateHDRMetadataBasedOnDisplayMode();

        /**
         * Calculate and set HDRMetadata and color space information.
        */
        virtual void SetHDRMetadataAndColorspace() = 0;

        /**
         * Get the internel implementation for api/platform parameter accessors.
        */
        virtual SwapChainInternel* GetImpl() = 0;
        virtual const SwapChainInternel* GetImpl() const = 0;

    private:
        NO_COPY(SwapChain)
        NO_MOVE(SwapChain)

    protected:
        SwapChain();

        // Helper to get formats
        ResourceFormat GetFormat(DisplayMode displayMode);

        virtual void CreateSwapChainRenderTargets() = 0;
        void DestroySwapChainRenderTargets();

        std::vector<uint64_t> m_BackBufferFences = {};
        uint8_t m_CurrentBackBuffer = 0;
        std::vector<DisplayMode> m_SupportedDisplayModes = {};
        DisplayMode m_CurrentDisplayMode = DisplayMode::DISPLAYMODE_LDR;
        HDRMetadata m_HDRMetadata = {};
        CommandQueue m_CreationQueue = CommandQueue::Graphics;
        bool m_TearingSupported = false;
        bool m_VSyncEnabled = false;

        ResourceFormat m_SwapChainFormat = ResourceFormat::Unknown;
        ResourceView* m_pSwapChainRTV = nullptr;
        SwapChainRenderTarget* m_pRenderTarget = nullptr;
    };
}