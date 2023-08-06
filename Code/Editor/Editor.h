#pragma once
#include <iostream>
#include "Framework/Engine.h"
#include "Framework/Function/Events/Event.h"
#include "Framework/Function/Events/ApplicationEvent.h"

namespace Rosefinch
{
    class Editor
    {
    public:
        Editor();
        virtual ~Editor();

        void Init(Engine* engineRuntime);
        void Run();

        void OnEvent(Event& e);
    protected:
        Engine* m_EngineRuntime {nullptr};

    private:
        bool OnWindowClose(const WindowCloseEvent& event);

    private:
        bool m_Running = true;
    };
}