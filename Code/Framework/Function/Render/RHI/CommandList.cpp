#include "CommandList.h"
#include "Framework/Function/Render/RHI/Device.h"
#include "Framework/Function/Render/RHI/Texture.h"
#include "Framework/Function/Render/RHI/UploadHeap.h"
#include "Framework/Function/GlobalContext.h"

namespace Rosefinch
{
    CommandList::CommandList(CommandQueue queueType) : m_QueueType(queueType)
    {}

    void CommandList::BeginVRSRendering(const VariableShadingRateInfo* pVrsInfo)
    {
        if (pVrsInfo->VariableShadingMode > VariableShadingMode::VariableShadingMode_None)
        {
            if (pVrsInfo->VariableShadingMode > VariableShadingMode::VariableShadingMode_Per_Draw &&
                pVrsInfo->Combiners[1] != ShadingRateCombiner::ShadingRateCombiner_Passthrough)
            {
                const GPUResource* vrsImage = pVrsInfo->pShadingRateImage->GetResource();
                Barrier barrier = Barrier::Transition(vrsImage, 
                                                      ResourceState::NonPixelShaderResource | ResourceState::PixelShaderResource, 
                                                      ResourceState::ShadingRateSource);
                ResourceBarrier(this, 1, &barrier);

                SetShadingRate(this, pVrsInfo->BaseShadingRate, pVrsInfo->Combiners, vrsImage);
            }
            else
            {
                SetShadingRate(this, pVrsInfo->BaseShadingRate, pVrsInfo->Combiners);
            }
        }
    }

    void CommandList::EndVRSRendering(const VariableShadingRateInfo* pVrsInfo) 
    {
        if (pVrsInfo->VariableShadingMode > VariableShadingMode::VariableShadingMode_None)
        {
            if (pVrsInfo->VariableShadingMode > VariableShadingMode::VariableShadingMode_Per_Draw &&
                pVrsInfo->Combiners[1] != ShadingRateCombiner::ShadingRateCombiner_Passthrough)
            {
                Barrier barrier = Barrier::Transition(pVrsInfo->pShadingRateImage->GetResource(),
                                                      ResourceState::ShadingRateSource,
                                                      ResourceState::NonPixelShaderResource | ResourceState::PixelShaderResource);
                ResourceBarrier(this, 1, &barrier);
            }

            // reset the combiners since VRS needs to be disabled
            ShadingRateCombiner combiners[2] = {ShadingRateCombiner::ShadingRateCombiner_Passthrough, ShadingRateCombiner::ShadingRateCombiner_Passthrough};
            SetShadingRate(this, ShadingRate::ShadingRate_1X1, combiners);
        }
    }

    UploadContext::~UploadContext() 
    {
        for (auto t: m_TransferInfos)
        {
            g_RuntimeGlobalContext.m_RenderSystem->GetUploadHeap()->EndResourceTransfer(t);
        }
    }

}

