#pragma once 
#include <memory>
#include <string>
#include "Framework/Function/Window/WindowSystem.h"
#include "Framework/Function/Render/RenderSystem.h"

namespace Rosefinch
{
    class WindowSystem;
    class RenderSystem;

    class GlobalContext
    {
    public:
        void StartSystems(const std::string& configFilePath);
        void ShutdownSystems();

    public:
        std::shared_ptr<WindowSystem> m_WindowSystem;
        std::shared_ptr<RenderSystem> m_RenderSystem;
    };

    extern GlobalContext g_RuntimeGlobalContext;
}