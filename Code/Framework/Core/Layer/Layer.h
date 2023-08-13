#pragma once
#include <string>
#include "Framework/Core/Base.h"
#include "Framework/Core/Events/Event.h"

namespace Rosefinch
{
    class Layer
    {
    public:
        Layer(const std::string& name="Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
}