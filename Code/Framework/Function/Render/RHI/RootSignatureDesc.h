#pragma once

#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RenderDefines.h"

namespace Rosefinch
{
    struct SamplerDesc;
    struct RootSignatureDescInternal;

    /**
     * @struct RootSignatureDesc
     *
     * The description structure used to construct RootSignature
     */
    struct RootSignatureDesc
    {
        /**
         * Get the pipeline type for the root signature to create
         */
        PipelineType GetPipelineType() const { return m_PipelineType; }

        RootSignatureDesc();

        virtual ~RootSignatureDesc();

        RootSignatureDesc(RootSignatureDesc&&) = delete;
        RootSignatureDesc(const RootSignatureDesc&&) = delete;

        /**
         * Move assignment operator. Handle impl memory in a custom fashion
        */
        RootSignatureDesc& operator=(RootSignatureDesc&&) noexcept;
        RootSignatureDesc& operator=(const RootSignatureDesc&&) noexcept;

        /**
         * Add a texture srv set to the signature description
        */
        void AddTextureSRVSet(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Add a texture uav set to the signature description
        */
        void AddTextureUAVSet(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Add a buffer src set to the signature description
        */
        void AddBufferSRVSet(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Add a buffer uav set to the signature description
        */
        void AddBufferUAVSet(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Add an rt acceleration structure set to the signature description
        */
        void AddRTAccelerationStructureSet(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Add a sampler set to the signature description
        */
        void AddSamplerSet(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Add a static sampler set to the signature description
        */
        void AddStaticSamplers(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count, const SamplerDesc* samplerDescList);

        /**
         * Add a constant buffer set to the signature description
        */
        void AddConstantBufferSet(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Add a constant buffer view to the signature description
        */
        void AddConstantBufferView(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Add a 32-bit push constant buffer to the signature description
        */
        void Add32BitConstantBuffer(uint32_t bindingIndex, ShaderBindStage bindStages, uint32_t count);

        /**
         * Sanity check to ensure root signature description is capable of being created
        */
        void UpdatePipelineType(ShaderBindStage bindStages);

        PipelineType m_PipelineType = PipelineType::Undefined;
        RootSignatureDescInternal *m_pSignatureDescImpl = nullptr;

    private:
        NO_COPY(RootSignatureDesc)
    };
}