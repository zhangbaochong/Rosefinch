#pragma once

namespace Rosefinch
{
    class RHIContext
    {
    public:
        virtual ~RHIContext() = 0;

        virtual void Init() = 0;
        virtual void PrepareContext() = 0;

        bool IsValidationLayerEnabled() const { return m_IsValidationLayerEnabled; }

    protected:
        bool m_IsValidationLayerEnabled {true};
    };
}