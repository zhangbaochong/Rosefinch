#pragma once
#include "Framework/Core/Layer/Layer.h"

#include <vulkan/vulkan.h>

namespace Rosefinch
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event &event) override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

        // TEST
        void SetupVulkan();

    private:
        VkInstance m_Instance {VK_NULL_HANDLE};
        VkPhysicalDevice m_PhysicalDevice{VK_NULL_HANDLE};
        VkDevice m_Device{VK_NULL_HANDLE};
    };
}