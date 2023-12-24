#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"
#include "Framework/Function/Render/RHI/ResourceView.h"
#include "Framework/Function/Render/Shaders/ShaderCommon.h"

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