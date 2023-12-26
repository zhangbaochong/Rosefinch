#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/CommandList.h"

#include <chrono>
#include <map>
#include <set>
#include <unordered_set>
#include <xstring>
#include <functional>

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
        bool Fullscreen : 1;

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
        bool BenchmarkJson : 1;

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

    class Device;
    class DynamicBufferPool;
    class DynamicResourcePool;
    class RasterViewAllocator;
    class ResourceResizedListener;
    class ResourceViewAllocator;
    class SwapChain;
    class UploadHeap;

    class RenderSystem final
    {
    public:
        RenderSystem() = default;
        ~RenderSystem();

        /**
         * Initialization.
        */
        void Init();

        /**
         *
         * Called to clean up everything when we are done.
        */
        void Shutdown();

        int32_t Run();

    public:
        const RenderConfig* GetConfig() const { return &m_RenderConfig; }

        /**
         * Retrieves the Device instance.
         */
        const Device* GetDevice() const { return m_pDevice; }
        Device* GetDevice() { return m_pDevice; }

        /**
         * Retrieves the ResourceViewAllocator instance.
         */
        const ResourceViewAllocator* GetResourceViewAllocator() const { return m_pResourceViewAllocator; }
        ResourceViewAllocator* GetResourceViewAllocator() { return m_pResourceViewAllocator; }

        /**
         * Retrieves the RasterViewAllocator instance.
         */
        const RasterViewAllocator* GetRasterViewAllocator() const { return m_pRasterViewAllocator; }
        RasterViewAllocator* GetRasterViewAllocator() { return m_pRasterViewAllocator; }

        /**
         * Retrieves the SwapChain instance.
         */
        const SwapChain* GetSwapChain() const { return m_pSwapChain; }
        SwapChain* GetSwapChain() { return m_pSwapChain; }

        /**
         * Retrieves the UploadHeap instance.
         */
        const UploadHeap* GetUploadHeap() const { return m_pUploadHeap; }
        UploadHeap* GetUploadHeap() { return m_pUploadHeap; }

        /**
         * Retrieves the DynamicBufferPool instance.
         */
        const DynamicBufferPool* GetDynamicBufferPool() const { return m_pDynamicBufferPool; }
        DynamicBufferPool* GetDynamicBufferPool() { return m_pDynamicBufferPool; }

        /**
         * Retrieves the DynamicResourcePool instance.
         */
        const DynamicResourcePool* GetDynamicResourcePool() const { return m_pDynamicResourcePool; }
        DynamicResourcePool* GetDynamicResourcePool() { return m_pDynamicResourcePool; }


    private:
        RenderConfig m_RenderConfig = {};

    protected:
        double m_DeltaTime = 0.0;
        uint64_t m_FrameID = -1;  // Start at -1, so that the first frame is 0
        CommandList* m_pCmdListForFrame = nullptr;

        Device* m_pDevice = nullptr;
        ResourceViewAllocator* m_pResourceViewAllocator = nullptr;
        RasterViewAllocator* m_pRasterViewAllocator = nullptr;
        SwapChain* m_pSwapChain = nullptr;
        UploadHeap* m_pUploadHeap = nullptr;
        DynamicBufferPool* m_pDynamicBufferPool = nullptr;
        DynamicResourcePool* m_pDynamicResourcePool = nullptr;

        std::mutex m_ResourceResizeMutex;
        std::unordered_set<ResourceResizedListener*> m_ResourceResizedListenders;
    };
}