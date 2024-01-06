#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"
#include <vector>

namespace Rosefinch
{
    struct Barrier;
    struct TextureCopyDesc;
    struct BufferCopyDesc;
    struct BufferAddressInfo;
    class CommandListInternal;
    struct ResourceViewInfo;
    class PipelineObject;
    class RasterView;
    class GPUResource;
    class ResourceViewAllocator;
    struct VariableShadingRateInfo;
    class Buffer;
    class IndirectWorkload;
    struct TransferInfo;
    class UploadContextInternal;

    class CommandList
    {
    public:
        virtual ~CommandList() = default;

        /**
         * CommandList instance creation function. Implemented per api/platform to return
         * the correct internal resource type.
        */
        static CommandList* CreateCommandList(const char* name, CommandQueue queueType, void* pInitParams);

        /**
         * Query whether we are currently between Begin/End Raster.
        */
        const bool GetRastering() const { return m_Rastering; }

        /**
         * Tells the CommandList we are doing rasterization work.
        */
        void SetRastering(bool state) { m_Rastering = state; }

        /**
         * Get the CommandQueue type for this CommandList.
        */
        CommandQueue GetQueueType() const { return m_QueueType; }

        virtual const CommandListInternal* GetImpl() const = 0;
        virtual CommandListInternal* GetImpl() = 0;

    private:
        NO_COPY(CommandList)
        NO_MOVE(CommandList)

        friend void BeginRaster(CommandList* pCmdList, uint32_t numRasterViews, const RasterView** pRasterViews,
                const RasterView* pDepthView, const VariableShadingRateInfo* pVrsInfo);
        void BeginVRSRendering(const VariableShadingRateInfo* pVrsInfo);

        friend void EndRaster(CommandList* pCmdList, const VariableShadingRateInfo* pVrsInfo);
        void EndVRSRendering(const VariableShadingRateInfo* pVrsInfo);

    protected:
        CommandList(CommandQueue queueType);

        CommandQueue m_QueueType = CommandQueue::Graphics;
        bool m_Rastering = false;
    };

    /**
     * @class UploadContext
     *
     * The api/platform-agnostic representation of an upload context.
     * Used to transfer asset data from CPU memory to GPU memory via the copy queue.
    */
    class UploadContext
    {
        /**
         * UploadContext instance creation function. Implementation per aip/platform to return
         * the correct internal resource type.
        */
        static UploadContext* CreateUploadContext();

        ~UploadContext();

        /**
         * Execute batched GPU resource copies
        */
        virtual void Execute() = 0;

        /**
         * Add TransferInfo data to the queue of resource copies to execute.
        */
        void AppendTransferInfo(TransferInfo* pTransferInfo) { m_TransferInfos.push_back(pTransferInfo); }

        virtual const UploadContextInternal* GetImpl() const = 0;
        virtual UploadContextInternal* GetImpl() = 0;

    private:
        NO_COPY(UploadContext)
            NO_MOVE(UploadContext)

    protected:
        UploadContext() = default;
        std::vector<TransferInfo*> m_TransferInfos = {};
    };
    /**
     * Set all resource view heaps to the CommandList.
    */
    void SetAllResourceViewHeaps(CommandList* pCmdList, ResourceViewAllocator* pAllocator = nullptr);

    /**
     * Closes the CommandList.
    */
    void CloseCmdList(CommandList* pCmdList);

    /**
     * Submit 1 (or more) resource barries.
    */
    void ResourceBarrier(CommandList* pCmdList, uint32_t barrierCount, const Barrier* pBarriers);

    /**
     * Copy texture data from one resource to another.
    */
    void CopyTextureRegion(CommandList* pCmdList, const TextureCopyDesc* pCopyDesc);

    /**
     * Copy buffer data from one resource to another.
    */
    void CopyBufferRegion(CommandList* pCmdList, const BufferCopyDesc* pCopyDesc);

    /**
     * Clear a render target with the specified value.
    */
    void ClearRenderTarget(CommandList* pCmdList, const ResourceViewInfo* pRenderTargetView, float clearColor[4]);

    /**
     * Clear a depth/stencil target with the specified value.
    */
    void ClearDepthStencil(CommandList* pCmdList, const ResourceViewInfo* pDepthStencilView, uint8_t stencilValue);

    /**
     * Clear a value with the specified value.
    */
    void ClearUAVFloat(CommandList* pCmdList, const GPUResource* pResource, const ResourceViewInfo* pGPUView, const ResourceViewInfo* pCPUView, float clearColor[4]);

    /**
     * Begin rasterization workload submission to the CommandList
    */
    void BeginRaster(CommandList* pCmdList, uint32_t numRasterViews, const RasterView** pRasterViews, const RasterView* pDepthView = nullptr, 
                    const VariableShadingRateInfo* pVrsInfo = nullptr);

    /**
     * End rasterization workload submission to the CommandList
    */
    void EndRaster(CommandList* pCmdList, const VariableShadingRateInfo* pVrsInfo = nullptr);   

    /**
     * Set a viewport for rasterization work
    */
    void SetViewport(CommandList* pCmdList, Viewport* pViewport); 

    /**
     * Set the scissor rect for the rasterization work
    */
    void SetScissorRects(CommandList* pCmdList, uint32_t numRects, Rect* pRectList);     

    /**
     * Convenience function to set both viewport and scissor rect though a single call.
    */
    void SetViewportScissorRect(CommandList* pCmdList, uint32_t left, uint32_t top, uint32_t width, uint32_t height, float nearDist, float farDist);

    /**
     * Set the pipeline object to user for Draw/Dispatch
    */
    void SetPipelineState(CommandList* pCmdList, PipelineObject* pPipeline);

    /**
     * Set the primitive topology to user on rasterization workloads
    */
    void SetPrimitiveTopology(CommandList* pCmdList, PrimitiveTopology topology);

    /**
     * Set a vertex buffer for rasterization work
    */
    void SetVertexBuffers(CommandList* pCmdList, uint32_t startSlot, uint32_t numBuffers, BufferAddressInfo* pVertexBufferView);

    /**
     * Set a index buffer for rasterization work
    */
    void SetIndexBuffer(CommandList* pCmdList, BufferAddressInfo* pIndexBufferView);

    /**
     * Instanced draw function
    */
    void DrawInstanced(CommandList* pCmdList, uint32_t vertexCountPerInstance, uint32_t instanceCount = 1, uint32_t startVertex = 0, uint32_t startInstance = 0);

    /**
     * Instanced drawindexed function
    */
    void DrawIndexdInstanced(CommandList* pCmdList, uint32_t indexCountPerInstance, uint32_t instanceCount = 1, uint32_t startIndex = 0, uint32_t baseVertex = 0, uint32_t startInstace = 0);

    /**
     * Execute indirect workload
    */
    void ExecuteIndirect(CommandList* pCmdList, IndirectWorkload* pIndirectWorkload, const Buffer* pArgumentBuffer, uint32_t drawCount, uint32_t offset);

    /**
     * Dispatch GPU workload
    */
    void Dispatch(CommandList* pCmdList, uint32_t numGroupX, uint32_t numGroupY, uint32_t numGroupZ);

    /**
     * Do immediate write to buffer resource
    */
    void WriteBufferImmediate(CommandList* pCmdList, const GPUResource* pResource, uint32_t numParams, const uint32_t* offsets, const uint32_t* values);

    /**
     * Set the shading rate to use for rasterization workload
    */
    void SetShadingRate(CommandList* pCmdList, const ShadingRate shadingRate, const ShadingRateCombiner* combiners, const GPUResource* pShadingRateImage = nullptr);

} // namespace Rosefinch
