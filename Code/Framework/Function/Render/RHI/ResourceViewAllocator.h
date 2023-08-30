#pragma once
#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RenderDefines.h"
#include "Framework/Function/Render/RHI/ResourceView.h"

namespace Rosefinch
{
    // Per platform/api implementation of ResourceViewAlloctor
    class ResourceViewAlloctorInternal;

    /**
     * @class ResourceViewAllocator
     * 
     * The api/platform-agnostic representation of the resource view allocator
    */
    class ResourceViewAllocator
    {
    public:
        /**
         * ResourceViewAllocator instance creation function. Implemented per api/platform to 
         * internal resource type
        */
        static ResourceViewAllocator* CreateResourceViewAllocator();

        virtual ~ResourceViewAllocator() = default;

        /**
         * Allocate CPU resource views
        */
        virtual void AllocateCPUResourceViews(ResourceView** ppResourceView, uint32_t count = 1) = 0;

        /**
         * Allocate GPU resource views
        */
        virtual void AllocateGPUResourceViews(ResourceView** ppResourceView, uint32_t count = 1) = 0;

        /**
         * Allocate GPU sampler views
        */
        virtual void AllocateGPUSamplerViews(ResourceView** ppResourceView, uint32_t count = 1) = 0;

        /**
         * Allocate CPU render views
        */
        virtual void AllocateCPURenderViews(ResourceView** ppResourceView, uint32_t count = 1) = 0;

        /**
         * Allocate CPU depth views
        */
        virtual void AllocateCPUDepthViews(ResourceView** ppResourceView, uint32_t count = 1) = 0;

        virtual ResourceViewAlloctorInternal* GetImpl() = 0;
        virtual const ResourceViewAlloctorInternal* GetImpl() const = 0;
        
    private:
        NO_COPY(ResourceViewAllocator)
        NO_MOVE(ResourceViewAllocator)

    protected:
        ResourceViewAllocator();

        uint32_t m_NumViews[static_cast<uint32_t>(ResourceViewHeapType::Count)];
    };
}