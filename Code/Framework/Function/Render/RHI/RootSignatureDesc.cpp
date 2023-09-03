#include "RootSignatureDesc.h"

namespace Rosefinch
{
    RootSignatureDesc &RootSignatureDesc::operator=(RootSignatureDesc &&right) noexcept
    {
        m_PipelineType = right.m_PipelineType;
        m_pSignatureDescImpl = right.m_pSignatureDescImpl;
        right.m_pSignatureDescImpl = nullptr;
        return *this;
    }

    RootSignatureDesc &RootSignatureDesc::operator=(const RootSignatureDesc &&right) noexcept
    {
        return this->operator=(const_cast<RootSignatureDesc &&>(right));
    }

    void RootSignatureDesc::UpdatePipelineType(ShaderBindStage bindStages)
    {
        if (static_cast<bool>(bindStages & ShaderBindStage::Vertex) ||
            static_cast<bool>(bindStages & ShaderBindStage::Pixel) ||
            static_cast<bool>(bindStages & ShaderBindStage::VertexAndPixel))
        {
            RosefinchAssert(ASSERT_CRITICAL, m_PipelineType == PipelineType::Graphics || m_PipelineType == PipelineType::Undefined, "Root signature is already set for another pipeline than graphic.");
            m_PipelineType = PipelineType::Graphics;
        }

        if (static_cast<bool>(bindStages & ShaderBindStage::Compute))
        {
            RosefinchAssert(ASSERT_CRITICAL, m_PipelineType == PipelineType::Compute || m_PipelineType == PipelineType::Undefined, "Root signature is already set for another pipeline than compute.");
            m_PipelineType = PipelineType::Compute;
        }
    }
}