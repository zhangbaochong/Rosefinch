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
    }

    GLFWwindow* WindowSystem::GetWindow() const
    {
        return m_Window;
    }
}