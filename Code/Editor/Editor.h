#pragma once
#include <iostream>

namespace Rosefinch
{
    class Editor
    {
    public:
        Editor();
        virtual ~Editor();

        void Init();
        void Run();
    };
}