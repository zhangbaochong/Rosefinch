#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RenderDefines.h"

namespace Rosefinch
{
    namespace RHI
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
        ///
        /// @ingroup CauldronRender
        enum class GPUResourceType
        {
            Texture = 0, ///< A texture resource. This is either a loaded texture, rendertarget or depthtarget
            Buffer,      ///< A buffer resource.
            Swapchain    ///< A Swapchain resource (special handling is provided).
        };

        /**
         * @class GPUResource
         *
         * The <c><i>Cauldron</i></c> api/platform-agnostic representation of a GPU resource.
         *
         * @ingroup CauldronRender
         */
        class GPUResource
        {
        public:
            /**
             * @brief   GPUResource instance creation function. Implemented per api/platform to return the correct
             *          internal resource type.
             */
            static GPUResource *CreateGPUResource(const wchar_t *resourceName, void *pOwner, ResourceState initialState, void *pInitParams, bool resizable = false);

            /**
             * @brief   Destruction with default behavior.
             */
            virtual ~GPUResource() = default;

            /**
             * @brief   Returns true if the resource is resizable, false otherwise.
             */
            bool IsResizable() const { return m_Resizable; }

            /**
             * @brief   Returns the resource's name.
             */
            const wchar_t *GetName() const { return m_Name.c_str(); }

            /**
             * @brief   Returns true if the resource is a <c><i>Texture</i></c>.
             */
            bool IsTexture() const { return m_OwnerType == OwnerType::Texture; }

            /**
             * @brief   Returns true if the resource is a <c><i>Buffer</i></c>.
             */
            bool IsBuffer() const { return m_OwnerType == OwnerType::Buffer; }

            /**
             * @brief   Returns true if the resource is a <c><i>CopyBuffer</i></c>.
             */
            bool IsCopyBuffer() const { return m_OwnerType == OwnerType::Memory; }

            /**
             * @brief   Sets the GPUResource's owner. This is either a Buffer, Texture, or CopyBuffer resource.
             */
            virtual void SetOwner(void *pOwner) = 0;

            /**
             * @brief   Returns the resource <c><i>Texture</i></c> pointer if the resource is a texture. Returns nullptr otherwise.
             */
            const Texture *GetTextureResource() const { return (m_OwnerType == OwnerType::Texture) ? m_pTexture : nullptr; }

            /**
             * @brief   Returns the resource <c><i>Buffer</i></c> pointer if the resource is a buffer. Returns nullptr otherwise.
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
            GPUResource(const wchar_t *resourceName, void *pOwner, ResourceState initialState, bool resizable);
            GPUResource() = delete;

            void InitSubResourceCount(uint32_t subResourceCount);

            std::wstring m_Name = L"";
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
        ///
        /// @ingroup CauldronRender
        enum class BarrierType
        {
            Transition, ///< Resource transition barrier
            Aliasing,   ///< Resource aliasing barrier
            UAV,        ///< Resource UAV-sync barrier
        };

        /// A structure encapsulating information needed for resource barrier execution.
        ///
        /// @ingroup CauldronRender
        struct Barrier
        {
            BarrierType Type;                  ///< The <c><i>BarrierType</i></c>.
            const GPUResource *pResource;      ///< The <c><i>GPUResource</i></c> to apply the barrier to.
            ResourceState SourceState;         ///< The source <c><i>ResourceState</i></c>.
            ResourceState DestState;           ///< The destination <c><i>ResourceState</i></c>.
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
}