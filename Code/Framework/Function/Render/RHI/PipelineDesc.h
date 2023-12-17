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

    // Structure representing the rasterization description needed for a pipeline object
    struct RasterDesc
    {
        bool Wireframe = false;                 // True if wireframe rendering is desired.
        CullMode CullingMode = CullMode::Front; // The culling mode to apply (defaults to CullingMode::Front)
        bool FrontCounterClockwise = false;     // Indicates if front-facing direction is counter-clockwise winding order (defaults to false)
        int32_t DepthBias = 0;                  // Depth bias to apply (defaults to 0)
        float DepthBiasClamp = 0.f;             // Depth bias clamping to apply (defaults to 0.f)
        float SlopeScaledDepthBias = 0.f;       // Sloped scaled depth bias to apply (defaults to 0.f)
        bool DepthClipEnable = true;            // True to enable depth clip (defaults to true)
        bool MultisampleEnable = false;         // True to enable mulitsample rasterization (defaults to false and currently unsupported)
    };

    // Structure representing to stencil description needed for a pipeline object
    struct StencilDesc
    {
        StencilOp StencilFailOp = StencilOp::Keep;
        StencilOp StencilDepthFailOp = StencilOp::Keep;
        StencilOp StencilPassOp = StencilOp::Keep;
        ComparisonFunc StencilFunc = ComparisonFunc::Always;
    };

    // Structure representing the depth description needed for a pipeline object
    struct DepthDesc
    {
        bool DepthEnable = false;
        bool DepthWriteEnable = false;
        ComparisonFunc DepthFunc = ComparisonFunc::Always;
        bool StencilEnable = false;
        uint8_t StencilReadMask = 0xff;
        uint8_t StencilWriteMask = 0x00;
        StencilDesc FrontFace = {};
        StencilDesc BackFace = {};
    };

    // Structure representing the input layout description for a single vertex attribute. Needed for a pipeline object
    struct InputLayoutDesc
    {
        VertexAttributeType AttributeType = VertexAttributeType::Position;  // Input layout attribute type
        ResourceFormat AttributeFmt = ResourceFormat::RGB32_FLOAT;          // Input layout attribute format
        uint32_t AttributeInputSlot = 0;                                    // Input layout attribute binding slot
        uint32_t AttributeOffset = 0;                                       // Input layout attribute data offset

        InputLayoutDesc(VertexAttributeType type, ResourceFormat format, uint32_t inputSlot, uint32_t offset) :
            AttributeType(type), AttributeFmt(format), AttributeInputSlot(inputSlot), AttributeOffset(offset) {}

        InputLayoutDesc() = delete;
    };

    // Per platform/API implementation of PipelineDesc;
    struct PipelineDescInternal;

    /**
     * @struct PipelineDesc
     *
     * The descrption used to build a pipeline object.
     * The minimal requirements for a PipelineDesc is a RootSignature and a Shader (for compute)
     * By default, the graphics pipeline desc will build with the following attribute:
     *  - No Depth Target
     *  - No Input Layout
     *  - Solid Fill and BackFace culling
     *  - No multisampling and 0 depth bias values
     *  - No blending
     *  - Depth disabled
     *  - Triangle topology
    */
    struct PipelineDesc
    {
        // Limit the number of render targets to 8
        static constexpr uint32_t s_MaxRenderTargets = 8;

        /**
         * Add a shader to the pipeline description
        */
        void AddShaderDesc(ShaderBuildDesc& shaderDesc);

        /**
         * Add a shader blob to the pipeline description
        */
        void AddShaderBlodDesc(ShaderBlobDesc& shaderBlobDesc);

        /**
         * Add the format of the render targets
        */
        void AddRasterFormats(const ResourceFormat& rtFormat, const ResourceFormat depthFormat = ResourceFormat::Unknown);
        void AddRasterFormats(const std::vector<ResourceFormat>& rtFormats, const ResourceFormat depthFormat = ResourceFormat::Unknown);

        PipelineDescInternal* GetImpl() { return m_PipelineImpl; }
        const PipelineDescInternal* GetImpl() const { return m_PipelineImpl; }

        /**
         * Construction, implemented per aip/platform
        */
        PipelineDesc();

        /**
         * Desctuction, implemented per api/platform
        */
        virtual ~PipelineDesc();

        PipelineDesc(PipelineDesc&&) = delete;
        PipelineDesc(const PipelineDesc&&) = delete;

        /**
         * Move assignment overload, implemented per api/platform
        */
        PipelineDesc& operator=(PipelineDesc&&) noexcept;
        PipelineDesc& operator=(const PipelineDesc&&) noexcept;

        /**
         * Set the root signature for the pipeline
        */
        void SetRootSignature(RootSignature* pRootSignature);

        /**
         * Add shader (and build them) when ready
        */
        void AddShaders(std::vector<const wchar_t*>* pAddtionalParamters = nullptr);

        /**
         * Define an input layout for the pipeline object (with manual information)
        */
        void AddInputLayout(std::vector<InputLayoutDesc>& inputLayouts);

        /**
         * Add rasterization state information (for graphics pipeline objects)
        */
        void AddRasterStateDescription(RasterDesc* pRasterDesc);

        /**
         * Add the format of the render targets
        */
        void AddRenderTargetFormats(const uint32_t numColorFormats, const ResourceFormat* pColorFormats, const ResourceFormat depthStencilFormat);

        /**
         * Add the blend states of the render targets
        */
        void AddBlendStates(const std::vector<BlendDesc>& blendDescs, bool alphaToCoverage, bool independentBlend);

        /**
         * Add the depth state
        */
        void AddDepthState(const DepthDesc* pDepthDesc);

        /**
         * Add primitive topology information
        */
        void AddPrimitiveTopolpgy(PrimitiveTopologyType topologyType);

        /**
         * Set wave64 for this pipeline
        */
        void SetWave64(bool isWave64);

        // TODO: Add support for SampleDesc, Flags, and Node information when it's needed

        PipelineType GetPipelineType() const { return m_PipelineType; }

        std::vector<ShaderBuildDesc> m_ShaderDescriptions = {};         // shader build descriptions (build shaders from string or file source)
        std::vector<ShaderBlobDesc> m_ShaderBlobDescriptions = {};      // shader build descriptions (build shaders from shader binary blob)

        bool m_IsWave64 = false;                                        // Sets this pipeline to operate with Wave64 if the shader blob doesn't have this information yet
        PipelineType m_PipelineType = PipelineType::Undefined;          // The pipeline type (compute or graphics)
        PipelineDescInternal* m_PipelineImpl = nullptr;                 // Internal implementation details set per api/platform   

    private:
        NO_COPY(PipelineDesc)
    };
} // namespace Rosefinch