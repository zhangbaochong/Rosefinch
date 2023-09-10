#pragma once

#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RenderDefines.h"

namespace Rosefinch
{
    /**
     * @struct ShaderBuildDesc
     *
     * A structure representing shader buld description information
    */
    struct ShaderBuildDesc
    {
        const char* ShaderCode = nullptr;           // shader source (can be string source or a file path)
        const char* EntryPoint = nullptr;           // shader entry point name
        const char* AdditionalParams = nullptr;     // shader addtional params
        ShaderStage Stage = ShaderStage::Compute;   // shader stage (default to ShaderStage::Compute)
        ShaderModel Model = ShaderModel::SM6_0;     // shader model to use 
        DefineList Defines;                         // shader defines to use in shader compiling

        /**
         * Convenience function to build a vertex shader build description
        */
        static inline ShaderBuildDesc Vertex(const char* shaderCode, const char* entryPoint, ShaderModel model = ShaderModel::SM6_0, DefineList* pDefines = nullptr)
        {
            ShaderBuildDesc desc;
            desc.ShaderCode = shaderCode;
            desc.EntryPoint = entryPoint;
            desc.Stage = ShaderStage::Vertex;
            desc.Model = model;

            if (pDefines)
            {
                desc.Defines = *pDefines;
            }

            return desc;
        }

        /**
         * Convenience function to build a pixel shader build description
        */
        static inline ShaderBuildDesc Pixel(const char* shaderCode, const char* entryPoint, ShaderModel model = ShaderModel::SM6_0, DefineList* pDefines = nullptr)
        {
            ShaderBuildDesc desc;
            desc.ShaderCode = shaderCode;
            desc.EntryPoint = entryPoint;
            desc.Stage = ShaderStage::Pixel;
            desc.Model = model;

            if (pDefines)
                desc.Defines = *pDefines;

            return desc;
        }

        /**
         * Convenience function to build a compute shader build description
        */
        static inline ShaderBuildDesc Compute(const char* shaderCode, const char* entryPoint, ShaderModel model = ShaderModel::SM6_0, DefineList* pDefines = nullptr)
        {
            ShaderBuildDesc desc;
            desc.ShaderCode = shaderCode;
            desc.EntryPoint = entryPoint;
            desc.Stage = ShaderStage::Compute;
            desc.Model = model;

            if (pDefines)
                desc.Defines = *pDefines;

            return desc;
        }
    };

    /**
     * @struct ShaderBlobDesc
     *
     * A struct representing shader blob description information
    */
    struct ShaderBlobDesc
    {
        const void* pData = nullptr;                // The shader binary to create the shader with.
        uint64_t DataSize = 0;                      // The size of the shader binary
        ShaderStage Stage = ShaderStage::Compute;   // The stage of the shader to build

        /**
         * Convenience function to build a vertex shader blob build description
        */
        static inline ShaderBlobDesc Vertex(const void* blobData, const uint64_t blobSize)
        {
            ShaderBlobDesc desc = { blobData, blobSize, ShaderStage::Vertex };
            return desc;
        }

        /**
         * Convenience function to build a pixel shader blob build description
        */
        static inline ShaderBlobDesc Pixel(const void* blobData, const uint64_t blobSize)
        {
            ShaderBlobDesc desc = { blobData, blobSize, ShaderStage::Pixel };
            return desc;
        }

        /**
         * Convenience function to build a compute shader blob build description
        */
        static inline ShaderBlobDesc Compute(const void* blobData, const uint64_t blobSize)
        {
            ShaderBlobDesc desc = { blobData, blobSize, ShaderStage::Compute };
            return desc;
        }
    };

    /**
     * Initialize the shader compilation system
    */
    int InitShaderCompileSystem();

    /**
     * Terminate the shader compilation system
    */
    void TeminateShaderCompileSystem();

    /**
     * Compile the shader description to byte code
    */
    void* CompileShaderToByteCode(const ShaderBuildDesc& shaderDesc, std::vector<const char*>* pAdditionalParameters = nullptr);
} // namespace Rosefinch