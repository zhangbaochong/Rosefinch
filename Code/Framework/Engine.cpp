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

    void Engine::Run() 
    {
        auto windowSystem = g_RuntimeGlobalContext.m_WindowSystem;
        if (!windowSystem)
        {
            LOG_CRITICAL("failed to get windowSystem");
        }

        while (!windowSystem->ShouldClose())
        {
            float deltaTime = 0.0f;
            TickOneFrame(deltaTime);
        }

    }

    void Engine::TickOneFrame(float deltaTime)
    {
        LogicalTick(deltaTime);

        RendererTick();

        g_RuntimeGlobalContext.m_WindowSystem->PollEvents();
    }

    void Engine::LogicalTick(float deltaTime) 
    {

    }

    void Engine::RendererTick() {}
}