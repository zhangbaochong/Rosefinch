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
            m_EngineRuntime->TickOneFrame(deltaTime);
            
            g_RuntimeGlobalContext.m_WindowSystem->PollEvents();
        }
    }

    void Editor::OnEvent(Event& e)
    {
        LOG_DEBUG(e.ToString());

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Editor::OnWindowClose));
    }

    bool Editor::OnWindowClose(const WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }
}