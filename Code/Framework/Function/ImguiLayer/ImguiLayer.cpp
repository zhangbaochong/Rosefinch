#include "ImGuiLayer.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
    {

    }

    void ImGuiLayer::OnAttach() 
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
    }

    void ImGuiLayer::OnDetach() 
    {

    }

    void ImGuiLayer::OnUpdate(float deltaTime) 
    {
        LOG_INFO("imgui layer");
    }

    void ImGuiLayer::OnEvent(Event &event) 
    {

    }
}