#include "WindowSystem.h"
#include "Framework/Core/Log/Log.h"
#include "Framework/Core/Events/ApplicationEvent.h"
#include "Framework/Core/Events/KeyEvent.h"
#include "Framework/Core/Events/MouseEvent.h"

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

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event); 
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event); 
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, false);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, true);
                    data.EventCallback(event);
                    break;
                }
            } 
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int codepoint)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(codepoint);
            data.EventCallback(event); 
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            } 
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xoffset, double yoffset)
         {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event); 
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });
    }

    GLFWwindow* WindowSystem::GetWindow() const
    {
        return m_Window;
    }

    void WindowSystem::PollEvents() const
    {
        glfwPollEvents();
    }
}