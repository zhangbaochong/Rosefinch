#include <iostream>
#include "Editor.h"
#include "Framework/Engine.h"

int main(int argv, char** argc)
{
    Rosefinch::Engine* engine = new Rosefinch::Engine(); 
    engine->StartEngine("");
    engine->Init();

    Rosefinch::Editor* editor = new Rosefinch::Editor();
    editor->Init(engine);
    editor->Run();

    engine->ShutdownEngine();
}