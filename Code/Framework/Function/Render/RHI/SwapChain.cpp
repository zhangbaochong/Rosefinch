#include "SwapChain.h"
#include "Framework/Function/GlobalContext.h"
#include "Framework/Function/Render/RHI/Texture.h"

namespace Rosefinch
{
    const char* SwapChain::s_SwapChainRTName = "SwapChainTarget";


    SwapChain::SwapChain()
    {
        // Setup fence tracking
        uint32_t backBufferCount = g_RuntimeGlobalContext.m_RenderSystem->GetConfig()->BackBufferCount;
        m_BackBufferFences.resize(backBufferCount);
        for (int i = 0; i < backBufferCount; i++)
        {
            m_BackBufferFences[i] = 0;
        }
    }

    SwapChain::~SwapChain()
    {
        DestroySwapChainRenderTargets();
        delete m_pRenderTarget;
        delete m_pSwapChainRTV;
    }

    size_t SwapChain::GetBackBufferCount()
    {
        return m_pRenderTarget->GetBackBufferCount();
    }

    ResourceFormat SwapChain::GetFormat(DisplayMode displayMode)
    {
        switch (displayMode)
        {
        case DisplayMode::DISPLAYMODE_LDR:
            return ResourceFormat::RGBA8_UNORM;
        case DisplayMode::DISPLAYMODE_FSHDR_2084:
        case DisplayMode::DISPLAYMODE_HDR10_2084:
            return ResourceFormat::RGB10A2_UNORM;
        case DisplayMode::DISPLAYMODE_FSHDR_SCRGB:
        case DisplayMode::DISPLAYMODE_HDR10_SCRGB:
            return ResourceFormat::RGBA16_FLOAT;
        default:
            return ResourceFormat::Unknown;
        }
    }

    DisplayMode SwapChain::CheckAndGetDisplayModeRequested(DisplayMode displayMode)
    {
        for (const auto& it : m_SupportedDisplayModes)
        {
            if (it == displayMode)
                return it;
        }

        if (displayMode == DisplayMode::DISPLAYMODE_FSHDR_2084) {

            RosefinchAssert(ASSERT_WARNING, false, "FSHDR PQ not supported, trying HDR10 PQ");
            return CheckAndGetDisplayModeRequested(DisplayMode::DISPLAYMODE_HDR10_2084);
        }
        else if (displayMode == DisplayMode::DISPLAYMODE_FSHDR_SCRGB) {

            RosefinchAssert(ASSERT_WARNING, false, "FSHDR SCRGB not supported, trying HDR10 SCRGB");
            return CheckAndGetDisplayModeRequested(DisplayMode::DISPLAYMODE_HDR10_SCRGB);
        }

        if (displayMode != DisplayMode::DISPLAYMODE_LDR)
        {
            RosefinchAssert(ASSERT_WARNING, false, "HDR modes not supported, defaulting to LDR");
        }

        return DisplayMode::DISPLAYMODE_LDR;
    }

    void SwapChain::PopulateHDRMetadataBasedOnDisplayMode()
    {
        switch (m_CurrentDisplayMode)
        {
            case DisplayMode::DISPLAYMODE_LDR:
                // Values set here make no difference on HDR wide gamut monitors
                // Monitors will not undersell their capabilities, if they can go beyond rec709 gamut and 100 nits.

                // [0, 1] in respective RGB channel maps to display gamut.
                m_HDRMetadata.RedPrimary[0] = 0.64f;
                m_HDRMetadata.RedPrimary[1] = 0.33f;
                m_HDRMetadata.GreenPrimary[0] = 0.30f;
                m_HDRMetadata.GreenPrimary[1] = 0.60f;
                m_HDRMetadata.BluePrimary[0] = 0.15f;
                m_HDRMetadata.BluePrimary[1] = 0.06f;
                m_HDRMetadata.WhitePoint[0] = 0.3127f;
                m_HDRMetadata.WhitePoint[1] = 0.3290f;

                // [0, 1] actually maps to display brightness.
                // This gets ignored, writing it for completeness
                m_HDRMetadata.MinLuminance = 0.0f;
                m_HDRMetadata.MaxLuminance = 100.0f;

                // Scene dependent
                m_HDRMetadata.MaxContentLightLevel = 2000.0f;
                m_HDRMetadata.MaxFrameAverageLightLevel = 500.0f;
                break;

            case DisplayMode::DISPLAYMODE_HDR10_2084:
                // Values set here either get clipped at display capabilities or tone and gamut mapped on the display to fit its brightness and gamut range.

                // rec 2020 primaries
                m_HDRMetadata.RedPrimary[0] = 0.708f;
                m_HDRMetadata.RedPrimary[1] = 0.292f;
                m_HDRMetadata.GreenPrimary[0] = 0.170f;
                m_HDRMetadata.GreenPrimary[1] = 0.797f;
                m_HDRMetadata.BluePrimary[0] = 0.131f;
                m_HDRMetadata.BluePrimary[1] = 0.046f;
                m_HDRMetadata.WhitePoint[0] = 0.3127f;
                m_HDRMetadata.WhitePoint[1] = 0.3290f;

                // Max nits of 500 is actually low
                // Can set this value to 1000, 2000 and 4000 based on target display and content contrast range
                // However we are trying to make sure HDR10 mode doesn't look bad on HDR displays with only 300 nits brightness, hence the low max lum value.
                m_HDRMetadata.MinLuminance = 0.0f;
                m_HDRMetadata.MaxLuminance = 500.0f;

                // Scene dependent
                m_HDRMetadata.MaxContentLightLevel = 2000.0f;
                m_HDRMetadata.MaxFrameAverageLightLevel = 500.0f;
                break;

            case DisplayMode::DISPLAYMODE_HDR10_SCRGB:
                // Same as above

                // rec 709 primaries
                m_HDRMetadata.RedPrimary[0] = 0.64f;
                m_HDRMetadata.RedPrimary[1] = 0.33f;
                m_HDRMetadata.GreenPrimary[0] = 0.30f;
                m_HDRMetadata.GreenPrimary[1] = 0.60f;
                m_HDRMetadata.BluePrimary[0] = 0.15f;
                m_HDRMetadata.BluePrimary[1] = 0.06f;
                m_HDRMetadata.WhitePoint[0] = 0.3127f;
                m_HDRMetadata.WhitePoint[1] = 0.3290f;

                // Same comment as HDR10_2084.
                m_HDRMetadata.MinLuminance = 0.0f;
                m_HDRMetadata.MaxLuminance = 500.0f;

                // Scene dependent
                m_HDRMetadata.MaxContentLightLevel = 2000.0f;
                m_HDRMetadata.MaxFrameAverageLightLevel = 500.0f;
                break;

            case DisplayMode::DISPLAYMODE_FSHDR_2084:
            case DisplayMode::DISPLAYMODE_FSHDR_SCRGB:
                // FS HDR modes should already have the monitor's primaries queried through backend API's like DXGI or VK ext

                // Scene dependent
                m_HDRMetadata.MaxContentLightLevel      = 2000.0f;
                m_HDRMetadata.MaxFrameAverageLightLevel = 500.0f;
                break;
        }
    }

    void SwapChain::DestroySwapChainRenderTargets()
    {
        if (m_pRenderTarget != nullptr)
        {
            m_pRenderTarget->ClearResources();
        }
    }
}