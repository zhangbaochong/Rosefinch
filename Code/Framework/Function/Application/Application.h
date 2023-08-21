#pragma once
#include <iostream>
#include "Framework/Engine.h"
#include "Framework/Core/Events/Event.h"
#include "Framework/Core/Events/ApplicationEvent.h"
#include "Framework/Core/Layer/LayerStack.h"
#include "Framework/Function/ImguiLayer/ImguiLayer.h"

int main(int argc, char** argv);

namespace Rosefinch
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        static Application& Get() { return *s_Instance; }
    protected:
        Engine* m_EngineRuntime {nullptr};

    private:
        bool OnWindowClose(const WindowCloseEvent& event);
        bool OnWindowResize(const WindowResizeEvent& event);

    private:
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_layerStack;
        ImGuiLayer* m_ImguiLayer;

    private:
        static Application* s_Instance;
        friend int ::main(int argc, char** argv);
    };

    // to be defined in client
    Application* CreateApplication();
}