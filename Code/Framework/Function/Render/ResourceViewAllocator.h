#pragma once
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    class ResourceViewAllocator
    {
    public:
        virtual ~ResourceViewAllocator() = default;

    private:
        NO_COPY(ResourceViewAllocator)
        NO_MOVE(ResourceViewAllocator)

    protected:
        ResourceViewAllocator();
    };
}