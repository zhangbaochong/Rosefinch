#include "WindowSystem.h"
#include "Framework/Core/Log/Log.h"

namespace Rosefinch
{
    WindowSystem::~WindowSystem()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void WindowSystem::Init(WindowCreateInfo createInfo)
    {
        if (!glfwInit())
        {
            LOG_CRITICAL("failed to init glfw.");
            return;
        }

        m_Width = createInfo.width;
        m_Height = createInfo.height;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_Window = glfwCreateWindow(m_Width, m_Height, createInfo.title, nullptr, nullptr);
        if (!m_Window)
        {
            LOG_CRITICAL("failed to create glfw window");
            glfwTerminate();
            return;
        }

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        LOG_INFO("{} extensions support", extensionCount);

        // while (!glfwWindowShouldClose(m_Window))
        // {
        //     glfwPollEvents();
        // }

        glfwSetWindowUserPointer(m_Window, this);
    }

    GLFWwindow *WindowSystem::GetWindow() const
    {
        return m_Window;
    }

    void WindowSystem::PollEvents() const
    {
        glfwPollEvents();
    }

    bool WindowSystem::ShouldClose() const 
    {
        return glfwWindowShouldClose(m_Window);
    }
}