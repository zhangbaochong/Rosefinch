#pragma once 

namespace Rosefinch
{
    /**
     * @class ResourceResizedListener
     * 
     * Convenience class to help constructs register for resize event notifications
    */
    class ResourceResizedListener
    {
    public:
        ResourceResizedListener() = default;
        virtual ~ResourceResizedListener();

        void MarkAsResizableResourceDependent();
        void MarkAsResizableResourceIndependent();

        virtual void OnResourceResized() = 0;
    };
} // namespace Rosefinch