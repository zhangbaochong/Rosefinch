#pragma once 
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Rosefinch
{
    struct WindowCreateInfo
    {
        int width {1920};
        int height {1080};
        const char* title {"Rosefinch Engine"};
        bool is_FullScreen {false};
    };

    class WindowSystem
    {
    public:
        WindowSystem() = default;
        ~WindowSystem();

        void Init(WindowCreateInfo createInfo);
        GLFWwindow* GetWindow() const;
        void PollEvents() const;
        bool ShouldClose() const;
        
    private:
        GLFWwindow* m_Window {nullptr};

        int m_Width {0};
        int m_Height {0};
        
    };
}