#include "window.h"

#include "core/assert.h"
#include "core/log.h"
#include "core/application.h"

#include <GLFW/glfw3.h>

namespace SoundStation
{
    Window::Window(const WindowSpecification &spec)
        : m_spec(spec)
    {
        int status = glfwInit();
        SS_ASSERT(status, "Failed to initialize GLFW!");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

        m_window = glfwCreateWindow(int(m_spec.width), int(m_spec.height), m_spec.title.c_str(), nullptr, nullptr);
        SS_ASSERT(m_window, "Failed to create window!");

        glfwMakeContextCurrent(m_window);

        SS_LOG_INFO(fmt::format("Created window: {} ({}, {})", m_spec.title, m_spec.width, m_spec.height));

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
            Application::instance().close();
        });
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