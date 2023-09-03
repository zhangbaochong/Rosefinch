#include "CopyResource.h"

namespace Rosefinch
{
    CopyResource::~CopyResource()
    {
        delete m_pResource;
    }
}