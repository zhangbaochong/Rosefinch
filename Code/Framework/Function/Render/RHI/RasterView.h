#pragma once 

#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/RenderDefines.h"
#include "Framework/Function/Render/RHI/ResourceView.h"
#include "Framework/Function/Render/RHI/ResourceResizedListener.h"

namespace Rosefinch
{
    class Texture;

    /**
     * @class RasterView
     * 
     * The RasterView representation of a rasterization resource view.
     * Needed to write to render targets and depth targets.
    */
    class RasterView final
    {
    public:
        ResourceViewInfo GetResourceView();
        const ResourceViewInfo GetResourceView() const;

    private:
        NO_COPY(RasterView)
        NO_MOVE(RasterView)

        friend class RasterViewAllocator;
        friend class CommandList;

        RasterView() = delete;
        RasterView(const Texture* pTex, ViewDimension dimension, int32_t mip = -1, int32_t arraySize = -1, int32_t firstArraySlice = -1);
        ~RasterView();

    private:
        const Texture* m_pTexture = nullptr;
        ViewDimension m_Dimension;
        int32_t m_Mip = -1;
        int32_t m_ArraySize = -1;
        int32_t m_FirstArraySlice = -1;

        ResourceView* m_pResourceView = nullptr;
    };

    /**
     * @class RasterViewAllocator
     * 
     * Allocator used for the creation of RasterView instances
    */
    class RasterViewAllocator final : public ResourceResizedListener
    {
    public:
        /**
         * Return a new RasterView instance mapped to the specified parameters
        */
        const RasterView* RequestRasterView(const Texture* pTex, ViewDimension dimension, int32_t mip = -1, int32_t arraySize = -1, int32_t firstArraySlice = -1);

        /**
         * Callback invoked when a resize event occurs. Rebind resized resources to their resource views.
        */
        void OnResourceResized() override;

    private:
        NO_COPY(RasterViewAllocator)
        NO_MOVE(RasterViewAllocator)

        friend class RenderSystem;
        RasterViewAllocator();
        ~RasterViewAllocator();

        RasterView* FindRasterView(const Texture* pTex, ViewDimension dimension, int32_t mip, int32_t arraySize, int32_t firstArraySlice);
    
    private:
        std::vector<std::pair<const Texture*, std::vector<RasterView*>>>  m_AllocatedRasterViews = {};
    };
} // namespace Rosefinch