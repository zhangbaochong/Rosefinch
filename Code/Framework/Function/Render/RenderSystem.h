#pragma once
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    struct RenderConfig
    {
        // Validation
        bool CPUValidationEnabled : 1;
        bool GPUValidationEnabled : 1;

        // Features
        bool VRSTier1 : 1;
        bool VRSTier2 : 1;
        bool RT_1_0 : 1;
        bool RT_1_1 : 1;
        bool FP16 : 1;

        // Presentation
        bool Vsync : 1;
        bool Fullscreen    : 1;

        // Other options
        bool DeveloperMode : 1;
        bool DebugShaders : 1;
        bool AGSEnabled : 1;
        bool StablePowerState : 1;
        bool InvertedDepth : 1;

        // RenderDoc
        bool EnableRenderDocCapture : 1;
        // Pix
        bool EnablePixCapture : 1;

        // Override Scene Samplers
        bool OverrideSceneSamplers : 1;

        // Perf Dump
        bool EnableBenchmark : 1;
        bool BenchmarkAppend : 1;
        bool BenchmarkJson   : 1;

        // Screen shot
        bool TakeScreenshot : 1;

        // FPS limiter
        bool LimitFPS : 1;
        bool GPULimitFPS : 1;

        // Acceleration Structure
        bool BuildRayTracingAccelerationStructure : 1;

        //////////////////////////////////////////////////////////////////////////
        // Non-binary data

        std::string MotionVectorGeneration = "";

        // FPS limiter
        uint32_t LimitedFrameRate = 240;

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