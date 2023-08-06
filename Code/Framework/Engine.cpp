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

    bool Engine::TickOneFrame(float deltaTime)
    {
        LogicalTick(deltaTime);

        RendererTick();

        g_RuntimeGlobalContext.m_WindowSystem->PollEvents();

        auto shouldWindowClose = g_RuntimeGlobalContext.m_WindowSystem->ShouldClose();
        return !shouldWindowClose;
    }

    void Engine::LogicalTick(float deltaTime) 
    {

    }

    void Engine::RendererTick() {}
}