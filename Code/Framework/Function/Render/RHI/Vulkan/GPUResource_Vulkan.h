#pragma once
#include "Framework/Function/Render/RHI/GPUResource.h"

namespace Rosefinch
{
    class GPUResourceInternal  final : public GPUResource
    {
    public:
        virtual ~GPUResourceInternal();

        void SetOwner(void *pOwner) override;
        
        virtual const GPUResourceInternal *GetImpl() const override { return this; } 
        virtual GPUResourceInternal *GetImpl() override { return this; }
    };
}