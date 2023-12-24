#pragma once

#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"

namespace Rosefinch
{
    class GPUResource;

    /**
     * @class CopyResource
     *
     * Copy resource are used to prime GPU resource with data (copied over via the Copy queue)
     */
    class CopyResource
    {
    public:
        /**
         * CopyResource instance creation function. Implemented per api/platform to return the correct
         * internal resource type
         */
        static CopyResource* CreateCopyResource(const GPUResource* pDest, void* pInitData, uint64_t dataSize, ResourceState initialSate);

        virtual ~CopyResource();

        /**
         * Get the backing GPUResource
         */
        GPUResource* GetResource() { return m_pResource; }
        const GPUResource* GetResource() const { return m_pResource; }

    private:
        NO_COPY(CopyResource)
            NO_MOVE(CopyResource)

    protected:
        CopyResource(void* pInitData, uint64_t dataSize) {}
        CopyResource() = delete;

        GPUResource* m_pResource = nullptr;
    };
}