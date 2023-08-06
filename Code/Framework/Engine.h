#pragma once
#include <string>

namespace Rosefinch
{
    class Engine
    {
    public:
        void StartEngine(const std::string configFilePath);
        void ShutdownEngine();

        void TickOneFrame(float deltaTime);
        void Init();

    protected:
        void LogicalTick(float deltaTime);
        void RendererTick();
    };
} // namespace Rosefinch
