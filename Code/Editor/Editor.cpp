#include "Editor.h"
#include "Framework/Core/Log/Log.h"
#include "Framework/Function/GlobalContext.h"

namespace Rosefinch
{
    Editor::Editor() {}

    Editor::~Editor() {}

    void Editor::Init()
    {
        g_RuntimeGlobalContext.StartSystems("");
    }

    void Editor::Run()
    {
        LOG_INFO("start editor");
        while (true)
        {
            
        }
    }
}