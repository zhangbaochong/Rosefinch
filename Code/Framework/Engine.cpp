#include "Engine.h"
#include "Framework/Function/GlobalContext.h"
#include "Framework/Function/Window/WindowSystem.h"
#include "Framework/Core/Log/Log.h"

namespace Rosefinch
{
    void Engine::StartEngine(const std::string configFilePath) 
    {
        g_RuntimeGlobalContext.StartSystems(configFilePath);
        LOG_INFO("start engine");
    }

    void Engine::ShutdownEngine() 
    {
        g_RuntimeGlobalContext.ShutdownSystems();
        LOG_INFO("shutdown engine");
    }

    void Engine::Init() 
    {

    }

    void Engine::TickOneFrame(float deltaTime)
    {
        LogicalTick(deltaTime);

        RendererTick();
    }

    void Engine::LogicalTick(float deltaTime) 
    {

    }

    void Engine::RendererTick() {}
}