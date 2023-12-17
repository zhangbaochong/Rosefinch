#include "ResourceResizedListener.h"

namespace Rosefinch
{
    ResourceResizedListener::~ResourceResizedListener()
    {
        MarkAsResizableResourceIndependent();
    }

    void ResourceResizedListener::MarkAsResizableResourceDependent()
    {
        // TODO GetFramework()->AddResizableResourceDependence(this);
    }

    void ResourceResizedListener::MarkAsResizableResourceIndependent()
    {
        // TODO: GetFramework()->RemoveResizableResourceDependence(this);
    }
} // namespace Rosefinch