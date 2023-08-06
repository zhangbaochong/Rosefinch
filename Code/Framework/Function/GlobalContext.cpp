#include "GlobalContext.h"
#include "Framework/Function/Window/WindowSystem.h"

namespace Rosefinch
{
    GlobalContext g_RuntimeGlobalContext;

    void GlobalContext::StartSystems(const std::string& configFilePath)
    {
        m_WindowSystem = std::make_shared<WindowSystem>();
        WindowCreateInfo createInfo;
        m_WindowSystem->Init(createInfo);
    }

    void GlobalContext::ShutdownSystems()
    {
        m_WindowSystem.reset();
    }
}