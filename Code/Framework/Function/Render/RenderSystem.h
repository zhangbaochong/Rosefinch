#pragma once
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    struct RenderConfig
    {
        // Presentation
        uint8_t BackBufferCount = 2;
        uint32_t Width = 1920;
        uint32_t Height = 1080;

        // Allocation sizes
        uint64_t UploadHeapSize = 100 * 1024 * 1024;
        uint32_t DynamicBufferPoolSize = 2 * 1024 * 1024;
        uint32_t GPUResourceViewCount = 10000;
        uint32_t CPUResourceViewCount = 100;
        uint32_t CPURenderViewCount = 100;
        uint32_t CPUDepthViewCount = 100;
        uint32_t GPUSamplerViewCount = 100;
    };

    class RenderSystem final
    {
    public:
        RenderSystem() = default;
        ~RenderSystem();

        void Init();

    public:
        const RenderConfig* GetConfig() const { return &m_RenderConfig; }

    private:
        RenderConfig m_RenderConfig = {};
    };
}