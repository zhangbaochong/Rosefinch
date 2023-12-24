#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"

namespace Rosefinch
{
    /**
     * A structure representing a sampler description
     */
    struct SamplerDesc
    {
        FilterFunc Filter = FilterFunc::MinMagMipLinear;   // Sampler filter function (default to linear)
        AddressMode AddressU = AddressMode::Clamp;         // Sampler U addressing mode (default to clamp)
        AddressMode AddressV = AddressMode::Clamp;         // Sampler V addressing mode (default to clamp)
        AddressMode AddressW = AddressMode::Clamp;         // Sampler W addressing mode (default to clamp)
        ComparisonFunc Comparison = ComparisonFunc::Never; // Sampler comparsion function (default to never)
        float MinLOD = 0.0f;                               // Sampler minimum LOD clamp (default to 0.0f)
        float MaxLOD = std::numeric_limits<float>::max();  // Sampler maximum LOD clamp (default to FLOAT_MAX)
        float MipLODBias = 0.0f;                           // Sampler mip LOD bias (default to 0.0f)
        uint32_t MaxAnisotropy = 16;                       // Sampler maximum anisotropy clamp (default to 16)

        // Sampler equals operator for runtime comparision
        bool operator==(const SamplerDesc& rhs) const
        {
            return !std::memcpy(this, &ths, sizeof(SamplerDesc));
        }
    };

    // Per platform/api implementation of Sampler
    class SamplerInternal;

    /**
     * @class
     *
     * The api/platform-agnostic representation of the sampler resource
     */
    class Sampler
    {
    public:
        /**
        * Sampler instance creation function. Implemented per api/platform to return the
        * correct internal resource type
        */
        static Sampler* CreateSampler(const char* name, const SamplerDesc& desc);

        virtual ~Sampler() = default;

        /**
         * Return the SamplerDesc used to construct the sampler
        */
        const SamplerDesc& GetDesc() const { return m_SamplerDesc; }

        virtual SamplerInternal* GetImpl() = 0;
        virtual const SamplerInternal* GetImpl() const = 0;

    private:
        NO_COPY(Sampler)
            NO_MOVE(Sampler)

    protected:
        Sampler(const char* name, const SamplerDesc& desc) : m_Name(name),
            m_SamplerDesc(desc)
        {
        }

        Sampler() = delete;

        std::string m_Name = "";
        SamplerDesc m_SamplerDesc = {};
    };
}