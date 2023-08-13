#pragma once
#include <iostream>
#include "Framework/Engine.h"
#include "Framework/Core/Events/Event.h"
#include "Framework/Core/Events/ApplicationEvent.h"
#include "Framework/Core/Layer/LayerStack.h"

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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    protected:
        Engine* m_EngineRuntime {nullptr};

    private:
        bool OnWindowClose(const WindowCloseEvent& event);
        bool OnWindowResize(const WindowResizeEvent& event);

    private:
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_layerStack;
    };
}