#include "GlobalContext.h"

namespace Rosefinch
{
    GlobalContext g_RuntimeGlobalContext;

    void GlobalContext::StartSystems(const std::string& configFilePath)
    {
        WindowCreateInfo createInfo;
        m_WindowSystem = std::make_shared<WindowSystem>(createInfo);

        m_RenderSystem = std::make_shared<RenderSystem>();
        m_RenderSystem->Init();
    }

    void GlobalContext::ShutdownSystems()
    {
        m_WindowSystem.reset();
    }
}