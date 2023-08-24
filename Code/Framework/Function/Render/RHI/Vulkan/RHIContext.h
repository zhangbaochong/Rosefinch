#pragma once
#include "Framework/Function/Render/RHI/RHIContext.h"

namespace Rosefinch
{
    namespace Vulkan
    {
        class RHIContext final : Rosefinch::RHIContext
        {
        public:
            virtual ~RHIContext() override final;

            virtual void Init() override final;
            virtual void PrepareContext() override final;
        };
    }
}