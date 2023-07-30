#include <iostream>
#include "Framework/Core/Log/Log.h"
import Editor;

int main(int argv, char** argc)
{
    std::cout << "Hello, Rosefinch" << std::endl;
    Rosefinch::Editor* editor = new Rosefinch::Editor();
    editor->Run();
    log();
}