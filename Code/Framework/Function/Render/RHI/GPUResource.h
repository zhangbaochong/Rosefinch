#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RenderDefines.h"

namespace Rosefinch
{

#define CAULDRON_MAX_SUB_RESOURCE 16

    // forward declaration
    class CommonResourceView;
    class Texture;
    class Buffer;

    bool IsSRGB(ResourceFormat format);
    bool IsDepth(ResourceFormat format);
    ResourceFormat ToGamma(ResourceFormat format);
    ResourceFormat FromGamma(ResourceFormat format);
    uint32_t GetResourceFormatStride(ResourceFormat format);

    class GPUResourceInternal;

    /// An enumeration of supported GPU resource types
    enum class GPUResourceType
    {
        Texture = 0, ///< A texture resource. This is either a loaded texture, rendertarget or depthtarget
        Buffer,      ///< A buffer resource.
        Swapchain    ///< A Swapchain resource (special handling is provided).
    };

    /**
     * @class GPUResource
     *
     * The api/platform-agnostic representation of a GPU resource.
     */
    class GPUResource
    {
    public:
        /**
         *  GPUResource instance creation function. Implemented per api/platform to return the correct
         *  internal resource type.
         */
        static GPUResource *CreateGPUResource(const wchar_t *resourceName, void *pOwner, ResourceState initialState, void *pInitParams, bool resizable = false);

        /**
         * Destruction with default behavior.
         */
        virtual ~GPUResource() = default;

        /**
         * Returns true if the resource is resizable, false otherwise.
         */
        bool IsResizable() const { return m_Resizable; }

        /**
         * Returns the resource's name.
         */
        const char *GetName() const { return m_Name.c_str(); }

        /**
         * Returns true if the resource is a Texture
         */
        bool IsTexture() const { return m_OwnerType == OwnerType::Texture; }

        /**
         * Returns true if the resource is a >Buffer
         */
        bool IsBuffer() const { return m_OwnerType == OwnerType::Buffer; }

        /**
         * @Returns true if the resource is a CopyBuffer
         */
        bool IsCopyBuffer() const { return m_OwnerType == OwnerType::Memory; }

        /**
         * Sets the GPUResource's owner. This is either a Buffer, Texture, or CopyBuffer resource.
         */
        virtual void SetOwner(void *pOwner) = 0;

        /**
         * Returns the resource Texture pointer if the resource is a texture. Returns nullptr otherwise.
         */
        const Texture *GetTextureResource() const { return (m_OwnerType == OwnerType::Texture) ? m_pTexture : nullptr; }

        /**
         * Returns the resource Buffer pointer if the resource is a buffer. Returns nullptr otherwise.
         */
        const Buffer *GetBufferResource() const { return (m_OwnerType == OwnerType::Buffer) ? m_pBuffer : nullptr; }

        /**
         * @brief   Gets the internal implementation for api/platform parameter accessors.
         */
        virtual const GPUResourceInternal *GetImpl() const = 0;
        virtual GPUResourceInternal *GetImpl() = 0;

        /**
         * @brief   Returns the current ResourceState the GPU resource is in.
         */
        ResourceState GetCurrentResourceState(uint32_t subResource = 0xffffffff) const;

        /**
         * @brief   Sets the GPU resource's ResourceState.
         */
        void SetCurrentResourceState(ResourceState newState, uint32_t subResource = 0xffffffff);

    private:
        // No copy, No move
        NO_COPY(GPUResource)
        NO_MOVE(GPUResource)

    protected:
        GPUResource(const char* resourceName, void *pOwner, ResourceState initialState, bool resizable);
        GPUResource() = delete;

        void InitSubResourceCount(uint32_t subResourceCount);

        std::string m_Name = "";
        bool m_Resizable = false;

        enum class OwnerType : uint32_t
        {
            None = 0, // Not yet assigned (init and swap chain resource init)
            Memory,   // Memory only resource (i.e. used for copies and as a holder etc.)
            Texture,  // Texture resource
            Buffer,   // Buffer resource
        } m_OwnerType = OwnerType::None;

        // Pointer to the owning resource
        union
        {
            void *m_pOwner = nullptr;
            Texture *m_pTexture;
            Buffer *m_pBuffer;
        };

        // States of all present sub-resources (first entry created by default to span all resources)
        std::vector<ResourceState> m_CurrentStates;
    };

    /// An enumeration of supported barrier types
    enum class BarrierType
    {
        Transition, ///< Resource transition barrier
        Aliasing,   ///< Resource aliasing barrier
        UAV,        ///< Resource UAV-sync barrier
    };

    /// A structure encapsulating information needed for resource barrier execution.
    struct Barrier
    {
        BarrierType Type;                  ///< The BarrierType
        const GPUResource *pResource;      ///< The GPUResource to apply the barrier to.
        ResourceState SourceState;         ///< The source ResourceState
        ResourceState DestState;           ///< The destination ResourceState
        uint32_t SubResource = 0xffffffff; ///< The sub-resource to transition (or -1 for whole resource).

        static Barrier Transition(const GPUResource *pRes, ResourceState srcState, ResourceState dstState, uint32_t subResource = 0xffffffff)
        {
            Barrier barrier = {BarrierType::Transition, pRes, srcState, dstState, subResource};
            return barrier;
        }

        static Barrier UAV(const GPUResource *pRes)
        {
            Barrier barrier = {BarrierType::UAV, pRes, ResourceState::UnorderedAccess, ResourceState::UnorderedAccess};
            return barrier;
        }
    };
}