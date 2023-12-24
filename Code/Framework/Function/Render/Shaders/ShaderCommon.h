#pragma once

enum class DisplayMode
{
    DISPLAYMODE_LDR,
    DISPLAYMODE_HDR10_2084,
    DISPLAYMODE_HDR10_SCRGB,
    DISPLAYMODE_FSHDR_2084,
    DISPLAYMODE_FSHDR_SCRGB
};

struct SwapchainCBData
{
    DisplayMode displayMode;
};