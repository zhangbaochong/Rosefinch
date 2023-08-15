#include "EditorUILayer.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Rosefinch
{
    EditorUILayer::EditorUILayer() : Layer("EditorUILayer")
    {

    }

    void EditorUILayer::OnAttach() 
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
    }

    void EditorUILayer::OnDetach() 
    {

    }

    void EditorUILayer::OnUpdate(float deltaTime) 
    {

    }

    void EditorUILayer::OnEvent(Event &event) 
    {

    }
}