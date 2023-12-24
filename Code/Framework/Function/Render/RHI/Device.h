#pragma once

#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"

namespace Rosefinch
{
    struct Barrier;
    struct BufferCopyDesc;
    class CommandList;
    class DeviceInternal;
    class SwapChain;
    struct SwapChainCreationParams;
    class Texture;
    struct TextureCopyDesc;

    // A structure representing variable shading rate information
    struct VariableShadingRateInfo
    {
        VariableShadingMode VariableShadingMode; ///< The VariableShadingMode to use.
        ShadingRate BaseShadingRate;             ///< The ShadingRate to use.
        const Texture* pShadingRateImage;        ///< The shading rate texture to use.
        ShadingRateCombiner Combiners[2];        ///< The ShadingRateCombiners to use.
        uint32_t ShadingRateTileWidth;           ///< The shading rate tile width.
        uint32_t ShadingRateTileHeight;          ///< The shading rate tile height.
    };

    class Device
    {
    public:
        /**
         * Device instance creation function. Implemented per api to return
         * the corrent internal resource type
         */
        static Device* CreateDevice();

        virtual ~Device();
        /**
         * Query if a request feature is supported
         */
        bool FeatureSupported(DeviceFeature requestedFeature) const { return (bool)(requestedFeature & m_SupportedFeatures); }

        /**
         * Return a feature information structure for features supporting feature queries
         */
        virtual void GetFeatureInfo(DeviceFeature feature, void* pFeatureInfo) = 0;

        /**
         * Query the highest supported shader model on the current device
         */
        ShaderModel MaxSupportedShaderModel() const { return m_MaxSupportedShaderModel; }

        /**
         * Get the min wave lane count information for the current device
         */
        uint32_t GetMinWaveLaneCount() const { return m_MinWaveLaneCount; }

        /**
         * Get the max wave lane count information for the current device
         */
        uint32_t GetMaxWaveLaneCount() const { return m_MaxWaveLaneCount; }

        /**
         * Flush all command queue
         */
        void FlushAllCommandQueues();

        /**
         * Runs the device through frame initialization, and returns a CommandList
         * to record into for the duration of the frame
         */
        CommandList* BeginFrame();

        /**
         * Ends the current frame. Also closes the current frame's CommandList and
         * submits it to the device for execution
         */
        void EndFrame();

        /**
         * Get the current device name
         */
        const char* GetDeviceName() const { return m_DeviceName.c_str(); }

        /**
         * Get the current driven version (requires AGS be enabled)
         */
        const char* GetDrivenVersion() const { return m_DrivenVersion.c_str(); }

        /**
         *  Get the graphics API in use
         */
        const char* GetGraphicsAPI() const { return m_GraphicAPI.c_str(); }

        /**
         * Get a short-form name for the used API
         */
        const char* GetGraphicsAPIShort() const { return m_GraphicAPIShort.c_str(); }

        /**
         * Get a pretty-fied string to use to present device name and API
         */
        const char* GetGraphicsAPIPretty() const { return m_GraphicAPIPretty.c_str(); }

        /**
         * Get the current graphics API version (required AGS be enabled)
         */
        const char* GetGraphicsAPIVersion() const { return m_GraphicAPIVersion.c_str(); }

        /**
         * Flush the specified queue
         */
        virtual void FlushQueue(CommandQueue queueType) = 0;

        /**
         * Query the performance counter frequency on a given queue
         */
        virtual uint64_t QueryPerformanceFrequency(CommandQueue queueType) = 0;

        /**
         * Create a CommandList
         */
        virtual CommandList* CreateCommandList(const char* name, CommandQueue queueType) = 0;

        /**
         * Create a SwapChain
         */
        virtual void CreateSwapChain(SwapChain*& pSwapChian, const SwapChainCreationParams& params, CommandQueue queueType) = 0;

        /**
         * For SwapChain present and signaling (for synchornization)
         */
        virtual uint64_t PresentSwapChain(SwapChain* pSwapChain) = 0;

        /**
         * Used to wait a signal value has been processed
         */
        virtual void WaitOnQueue(uint64_t waitValue, CommandQueue queueType) const = 0;

        /**
         * Execute the provided command lists, returns a signal ID that can be used to query completion
         */
        virtual uint64_t ExecuteCommandLists(std::vector<CommandList*> cmdLists, CommandQueue queueType, bool isLastSubmissionOfFrame = false) = 0;

        /**
         * Similar to ExecuteCommandLists, but will wait until completion
         */
        virtual void ExecuteCommandListsImmediate(std::vector<CommandList*> cmdLists, CommandQueue queueType) = 0;

        /**
         * Transition a resource in place (blocking call)
         */
        virtual void ExecuteResourceTransitionImmediate(uint32_t barrierCount, const Barrier* pBarriers) = 0;

        /**
         * Copy to a texture resource in place (blocking call)
         */
        virtual void ExecuteTextureResourceCopyImmediate(uint32_t resourceCopyCount, const TextureCopyDesc* pCopyDescs) = 0;

        /**
         * Set VariableShadingRateInfo to use
         */
        void SetVRSInfo(const VariableShadingRateInfo& variableShadingRateInfo) { m_VariableShadingRateInfo = variableShadingRateInfo; }

        const VariableShadingRateInfo* GetVRSInfo() const { return &m_VariableShadingRateInfo; }

        virtual const DeviceInternal* GetImpl() const = 0;
        virtual DeviceInternal* GetImpl() = 0;

    protected:
        Device();
        void DeleteCommandListAsync(void* pInFlightGPUInfo);

    private:
        NO_COPY(Device);
        NO_MOVE(Device);

    protected:
        struct GPUExecutionPacket
        {
            std::vector<CommandList*> CmdLists = {};
            uint64_t CompletionID = 0;

            GPUExecutionPacket(std::vector<CommandList*>& cmdLists, uint64_t completionID) : CmdLists(std::move(cmdLists)), CompletionID(completionID) {}
            GPUExecutionPacket() = delete;
        };

        DeviceFeature m_SupportedFeatures = DeviceFeature::None;
        // vk doesn't support these queries, set to min without RT and 32 waves for now
        ShaderModel m_MaxSupportedShaderModel = ShaderModel::SM6_2;
        uint32_t m_MinWaveLaneCount = 32;
        uint32_t m_MaxWaveLaneCount = 32;

        VariableShadingRateInfo m_VariableShadingRateInfo;
        // Graphics command lists
        CommandList* m_pActiveCommandList = nullptr;

        // TODO: add async compute command lists
        const std::string NOT_SET = "Not Set";
        std::string m_DeviceName = NOT_SET;
        std::string m_DrivenVersion = NOT_SET;
        std::string m_GraphicAPI = NOT_SET;
        std::string m_GraphicAPIShort = NOT_SET;
        std::string m_GraphicAPIPretty = NOT_SET;
        std::string m_GraphicAPIVersion = NOT_SET;
    };
}