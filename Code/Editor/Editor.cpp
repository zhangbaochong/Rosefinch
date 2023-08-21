#include "EditorLayer.h"
#include "Framework/Function/Application/EntryPoint.h"
#include "Framework/Function/Application/Application.h"

namespace Rosefinch
{
    class Editor : public Application
    {
    public:
        Editor() : Application()
        {
            PushLayer(new EditorLayer());
        }
    };

    Application* CreateApplication()
    {
        return new Editor();
    }

}