#pragma once 
#include <memory>
#include <string>
#include "Framework/Function/Window/WindowSystem.h"

namespace Rosefinch
{
    class WindowSystem;

    class GlobalContext
    {
    public:
        void StartSystems(const std::string& configFilePath);
        void ShutdownSystems();

    public:
        std::shared_ptr<WindowSystem> m_WindowSystem;

    };

    extern GlobalContext g_RuntimeGlobalContext;
}