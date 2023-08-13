#include "Editor.h"
#include "Framework/Core/Log/Log.h"
#include "Framework/Function/GlobalContext.h"
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    Editor::Editor() {}

    Editor::~Editor() {}

    void Editor::Init(Engine* engineRuntime)
    {
        assert(engineRuntime);
        m_EngineRuntime = engineRuntime;

        g_RuntimeGlobalContext.m_WindowSystem->SetEventCallback(HZ_BIND_EVENT_FN(Editor::OnEvent));
    }

    void Editor::Run()
    {
        LOG_INFO("start editor");
        while (m_Running)
        {
            float deltaTime = 0.0f; // TODO cal deltaTime

            if (!m_Minimized)
            {
                for (Layer* layer: m_layerStack)
                {
                    layer->OnUpdate(deltaTime);
                }
            }

            m_EngineRuntime->TickOneFrame(deltaTime);
            g_RuntimeGlobalContext.m_WindowSystem->PollEvents();
        }
    }

    void Editor::OnEvent(Event& e)
    {
        LOG_DEBUG(e.ToString());

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Editor::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Editor::OnWindowResize));

        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
        {
            if (e.Handled)
            {
                break;
            }
            (*it)->OnEvent(e);
        }
    }

    bool Editor::OnWindowClose(const WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    bool Editor::OnWindowResize(const WindowResizeEvent& event)
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

    void Editor::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Editor::PushOverlay(Layer* overlay)
    {
        m_layerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
}