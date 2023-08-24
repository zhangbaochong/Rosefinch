#pragma once
#include <vector>
#include <string>
#include "Framework/Core/Base.h"
#include <vulkan/vulkan.h>

namespace Rosefinch
{
    namespace Vulkan
    {
        using StringList = std::vector<std::string>;
        using RawStringList = std::vector<const char*>;

        bool IsSuccess(VkResult result);
        bool IsError(VkResult result);
    }
}