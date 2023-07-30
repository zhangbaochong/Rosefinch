#include <iostream>
#include "Editor.h"

int main(int argv, char** argc)
{
    Rosefinch::Editor* editor = new Rosefinch::Editor();
    editor->Run();
}