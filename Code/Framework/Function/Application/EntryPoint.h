#pragma once
#include "Application.h"

extern Rosefinch::Application* Rosefinch::CreateApplication();

int main(int argv, char** argc)
{
    auto app = Rosefinch::CreateApplication();

    app->Run();

    delete app;
}