#include "Framework/Function/Render/RHI/ShaderBuilder.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING    // To avoid receiving deprecation error since we are using C++11 only
#include <experimental/filesystem>
using namespace std::experimental;
#include <sstream>

#include <wrl.h>
#include <dxc/dxcapi.h>

namespace Rosefinch
{
    int InitShaderCompileSystem()
    {
        return 0;
    }


    void TeminateShaderCompileSystem()
    {

    }


    void* CompileShaderToByteCode(const ShaderBuildDesc& shaderDesc, std::vector<const char*>* pAdditionalParameters)
    {
        return nullptr;
    }
}