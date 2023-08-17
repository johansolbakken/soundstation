#include "window.h"

#include "core/assert.h"
#include "core/log.h"

#include <GLFW/glfw3.h>

namespace SoundStation
{
    Window::Window(const WindowSpecification &spec)
        : m_spec(spec)
    {
        int status = glfwInit();
        SS_ASSERT(status, "Failed to initialize GLFW!");

        m_window = glfwCreateWindow(int(m_spec.width), int(m_spec.height), m_spec.title.c_str(), nullptr, nullptr);
        SS_ASSERT(m_window, "Failed to create window!");

        glfwMakeContextCurrent(m_window);

        SS_LOG_INFO(fmt::format("Created window: {} ({}, {})", m_spec.title, m_spec.width, m_spec.height));
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
}