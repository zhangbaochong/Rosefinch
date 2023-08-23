#include "Application.h"
#include "Framework/Core/Log/Log.h"
#include "Framework/Function/GlobalContext.h"
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    Application* Application::s_Instance = nullptr;

    Application::Application() 
    {
        s_Instance = this;

        m_EngineRuntime = new Rosefinch::Engine(); 
        m_EngineRuntime->StartEngine("");
        m_EngineRuntime->Init();

        g_RuntimeGlobalContext.m_WindowSystem->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

        m_ImguiLayer = new ImGuiLayer();
        PushOverlay(m_ImguiLayer);
    }

    Application::~Application() 
    {
        m_EngineRuntime->ShutdownEngine();
    }

    void Application::Run()
    {
        LOG_INFO("start editor");
        while (m_Running)
        {
            float deltaTime = 0.0f; // TODO cal deltaTime

            if (!m_Minimized)
            {
                for (Layer* layer: m_LayerStack)
                {
                    layer->OnUpdate(deltaTime);
                }

                m_ImguiLayer->Begin();
                {
                    for (Layer* layer: m_LayerStack)
                    {
                        layer->OnImGuiRender();
                    }
                }
                m_ImguiLayer->End();
            }

            m_EngineRuntime->TickOneFrame(deltaTime);
            g_RuntimeGlobalContext.m_WindowSystem->PollEvents();
        }
    }

    void Application::OnEvent(Event& e)
    {
        LOG_DEBUG(e.ToString());

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.Handled)
            {
                break;
            }
            (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(const WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(const WindowResizeEvent& event)
    {
        if (event.GetWidth() == 0 || event.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;

        // TODO Render change surface size

        return false;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
}