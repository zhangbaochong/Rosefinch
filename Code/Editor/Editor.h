#pragma once
#include <iostream>
#include "Framework/Engine.h"

namespace Rosefinch
{
    class Editor
    {
    public:
        Editor();
        virtual ~Editor();

        void Init(Engine* engineRuntime);
        void Run();

    protected:
        Engine* m_EngineRuntime {nullptr};
    };
}