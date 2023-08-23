#include "ImGuiLayer.h"
#include "Framework/Core/Base.h"
#include "Framework/Function/GlobalContext.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <glfw/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>

namespace Rosefinch
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
    {
    }

    void ImGuiLayer::OnAttach()
    {
        LOG_DEBUG("ImGui Layer Attack.");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // enable keyboard control
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // set fonts --TODO

        ImGui::StyleColorsDark();

        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForVulkan(g_RuntimeGlobalContext.m_WindowSystem->GetWindow(), true);
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(Event &event)
    {
    }

    void ImGuiLayer::OnImGuiRender()
    {

    }

    void ImGuiLayer::Begin()
    {
        // ImGui_ImplVulkan_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        // ImGuiIO& io = ImGui::GetIO();
		// io.DisplaySize = ImVec2((float)g_RuntimeGlobalContext.m_WindowSystem->GetWidth(), (float)(float)g_RuntimeGlobalContext.m_WindowSystem->GetHeight());

		// // Rendering
		// ImGui::Render();

        // //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData());

		// if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		// {
		// 	GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
		// 	ImGui::UpdatePlatformWindows();
		// 	ImGui::RenderPlatformWindowsDefault();
		// 	glfwMakeContextCurrent(backupCurrentContext);
		// }
    }
}