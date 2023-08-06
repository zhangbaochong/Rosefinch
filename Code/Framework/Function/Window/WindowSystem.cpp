#include "WindowSystem.h"
#include "Framework/Core/Log/Log.h"
#include "Framework/Function/Events/ApplicationEvent.h"
#include "Framework/Function/Events/KeyEvent.h"
#include "Framework/Function/Events/MouseEvent.h"

namespace Rosefinch
{
    WindowSystem::WindowSystem(WindowCreateInfo createInfo)
    {
        this->Init(createInfo);
    }

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

        m_Data.Width = createInfo.width;
        m_Data.Height = createInfo.height;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, createInfo.title, nullptr, nullptr);
        if (!m_Window)
        {
            LOG_CRITICAL("failed to create glfw window");
            glfwTerminate();
            return;
        }

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        LOG_INFO("{} extensions support", extensionCount);

        glfwSetWindowUserPointer(m_Window, &m_Data);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });
    }

    GLFWwindow *WindowSystem::GetWindow() const
    {
        return m_Window;
    }

    void WindowSystem::PollEvents() const
    {
        glfwPollEvents();
    }
}