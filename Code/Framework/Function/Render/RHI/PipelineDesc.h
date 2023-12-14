#pragma once

#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RenderDefines.h"
#include "Framework/Function/Render/RHI/RootSignature.h"
#include "Framework/Function/Render/RHI/ShaderBuilder.h"

namespace Rosefinch
{
    // Structure representing the blend description needed for a pipeline object
    struct BlendDesc
    {
        bool BlendEnabled = false;
        Blend SourceBlendColor = Blend::One;
        Blend DestBlendColor = Blend::Zero;
        BlendOp ColorOp = BlendOp::Add;
        Blend SourceBlendAlpha = Blend::One;
        Blend DestBlendAlpha = Blend::Zero;
        BlendOp AlphaOp = BlendOp::Add;
        uint32_t RenderTargetWriteMask = static_cast<uint32_t>(ColorWriteMask::All);
    };
} // namespace Rosefinch