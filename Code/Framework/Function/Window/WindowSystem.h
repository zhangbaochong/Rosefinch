#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Framework/Function/Events/Event.h"

namespace Rosefinch
{
    struct WindowCreateInfo
    {
        int width{1920};
        int height{1080};
        const char *title{"Rosefinch Engine"};
        bool is_FullScreen{false};
    };

    class WindowSystem
    {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        WindowSystem(WindowCreateInfo createInfo);
        ~WindowSystem();

        GLFWwindow *GetWindow() const;
        void PollEvents() const;

        void SetEventCallback(const EventCallbackFn &callback) { m_Data.EventCallback = callback; }
    private:
        void Init(WindowCreateInfo createInfo);
        GLFWwindow *m_Window{nullptr};

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}