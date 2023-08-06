#include "Editor.h"
#include "Framework/Core/Log/Log.h"
#include "Framework/Function/GlobalContext.h"

namespace Rosefinch
{
    Editor::Editor() {}

    Editor::~Editor() {}

    void Editor::Init(Engine* engineRuntime)
    {
        assert(engineRuntime);
        m_EngineRuntime = engineRuntime;
    }

    void Editor::Run()
    {
        LOG_INFO("start editor");
        while (true)
        {
            float deltaTime = 0.0f; // TODO cal deltaTime
            if (!m_EngineRuntime->TickOneFrame(deltaTime))
            {
                return;
            }
        }
    }
}