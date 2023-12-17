#include "PipelineDesc.h"
#include "Framework/Function/GlobalContext.h"

namespace Rosefinch
{
    // Move operators
    PipelineDesc& PipelineDesc::operator=(PipelineDesc&& right) noexcept
    {
        m_ShaderDescriptions = right.m_ShaderDescriptions;
        m_ShaderBlobDescriptions = right.m_ShaderBlobDescriptions;

        m_PipelineType = right.m_PipelineType;
        m_PipelineImpl = right.m_PipelineImpl;
        right.m_PipelineImpl = nullptr;
        return *this;
    }

    PipelineDesc& PipelineDesc::operator=(const PipelineDesc&& right) noexcept
    {
        return this->operator=(const_cast<PipelineDesc&&>(right));
    }

    void PipelineDesc::AddShaderDesc(ShaderBuildDesc& shaderDesc)
    {
        if (shaderDesc.Stage == ShaderStage::Compute)
        {
            RosefinchAssert(ASSERT_CRITICAL, m_PipelineType == PipelineType::Compute || m_PipelineType
             == PipelineType::Undefined, "Compute shader has been added a pipeline description that isn't a compute one. Terminating due to invalid behavior");
            m_PipelineType = PipelineType::Compute;
        }
        else
        {
            RosefinchAssert(ASSERT_CRITICAL, m_PipelineType == PipelineType::Graphics || m_PipelineType == PipelineType::Undefined, "Graphics shader has been added a pipeline description that isn't a graphics one. Terminating due to invalid behavior");
            m_PipelineType = PipelineType::Graphics;
        }

        // Append defines for near/far depth
        static bool s_InvertedDepth = g_RuntimeGlobalContext.m_RenderSystem->GetConfig()->InvertedDepth;
        if (s_InvertedDepth)
        {
            shaderDesc.Defines.insert(std::make_pair("FAR_DEPTH", "0.0"));
            shaderDesc.Defines.insert(std::make_pair("NEAR_DEPTH", "1.0"));
        }
        else
        {
            shaderDesc.Defines.insert(std::make_pair("FAR_DEPTH", "1.0"));
            shaderDesc.Defines.insert(std::make_pair("NEAR_DEPTH", "0.0"));
        }

        m_ShaderDescriptions.push_back(shaderDesc);
    }

    void PipelineDesc::AddShaderBlodDesc(ShaderBlobDesc& shaderBlobDesc)
    {
        if (shaderBlobDesc.Stage == ShaderStage::Compute)
        {
            RosefinchAssert(ASSERT_CRITICAL,
                           m_PipelineType == PipelineType::Compute || m_PipelineType == PipelineType::Undefined,
                           "Compute shader has been added a pipeline description that isn't a compute one. Terminating due to invalid behavior");
            m_PipelineType = PipelineType::Compute;
        }
        else
        {
            RosefinchAssert(ASSERT_CRITICAL,
                           m_PipelineType == PipelineType::Graphics || m_PipelineType == PipelineType::Undefined,
                           "Graphics shader has been added a pipeline description that isn't a graphics one. Terminating due to invalid behavior");
            m_PipelineType = PipelineType::Graphics;
        }

        m_ShaderBlobDescriptions.push_back(shaderBlobDesc);
    }

    void PipelineDesc::AddRasterFormats(const ResourceFormat& rtFormat, const ResourceFormat depthFormat /*= ResourceFormat::Unknown*/)
    {
        RosefinchAssert(ASSERT_CRITICAL, rtFormat != ResourceFormat::Unknown || depthFormat != ResourceFormat::Unknown, "There are no formats to pass to the pipeline description.");
        AddRenderTargetFormats(1, &rtFormat, depthFormat);
    }

    void PipelineDesc::AddRasterFormats(const std::vector<ResourceFormat>& rtFormats, const ResourceFormat depthFormat /*= ResourceFormat::Unknown*/)
    {
        RosefinchAssert(ASSERT_CRITICAL, rtFormats.size() || depthFormat != ResourceFormat::Unknown, "There are no formats to pass to the pipeline description.");
        AddRenderTargetFormats((uint32_t)rtFormats.size(), rtFormats.data(), depthFormat);
    }

    void PipelineDesc::SetWave64(bool isWave64)
    {
        m_IsWave64 = isWave64;
    }
} // namespace Rosefinch