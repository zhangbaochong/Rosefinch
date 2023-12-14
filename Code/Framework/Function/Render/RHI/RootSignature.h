#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RenderDefines.h"
#include "Framework/Function/Render/RHI/RootSignatureDesc.h"

namespace Rosefinch
{
    /**
     * @struct BindingDesc
     *
     * Structure representing a binding description for resource binding
     */
    struct BindingDesc
    {
        BindingType Type = BindingType::Invalid; // The binding type
        uint32_t BaseShaderRegister = 0;         // Shader register to bind to
        uint32_t BindingIndex = 0;               // Shader space to bind to
        uint32_t Count = 0;                      // Number of bound resource
    };

    // Per platform/api implementation of RootSignature
    class RootSignatureInternal;

    /**
     * @class RootSignature
     *
     * The api/platform-agnostic representation of the root signature
     */
    class RootSignature
    {
    public:
        /**
         * RootSignature instance creation function. Implemented per api/platform to return
         * the correct resource type
         */
        static RootSignature* CreateRootSignature(const char* name, const RootSignatureDesc& desc);

        virtual ~RootSignature() = default;

        PipelineType GetPipelineType() const { return m_PipelineType; }

        const char* GetName() const { return m_Name.c_str(); }

        /**
         * Return the vector of binding descriptions
         */
        const std::vector<BindingDesc>& GetBindingDescriptions() const { return m_BindingDescriptions; }

        /**
         * Return the binding description offset by bingding type
         */
        const int32_t GetBindingDescOffset(BindingType bindType) const { return m_BindingDescOffsets[static_cast<uint32_t>(bindType)]; }

        /**
         * Get the internal implementation for api/platform parameter accessors
         */
        virtual RootSignatureInternal* GetImpl() = 0;
        virtual const RootSignatureInternal* GetImpl() const = 0;

    private:
        NO_COPY(RootSignature)
        NO_MOVE(RootSignature)

        virtual void Build(const RootSignatureDesc& desc) = 0;

    protected:
        RootSignature(const char* name) : m_Name(name) {}
        RootSignature() = delete;

    protected:
        PipelineType m_PipelineType = PipelineType::Undefined;
        std::string m_Name = "";
        std::vector<BindingDesc> m_BindingDescriptions;
        int32_t m_BindingDescOffsets[static_cast<uint32_t>(BindingType::Count)] = { -1 };
    };
}