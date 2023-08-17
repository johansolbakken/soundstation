#pragma once

#include <string>

struct GLFWwindow;

namespace SoundStation
{
    struct WindowSpecification
    {
        std::string title;
        uint32_t width;
        uint32_t height;
    };

    class Window
    {
    public:
        Window(const WindowSpecification &spec);
        ~Window();

        void onUpdate();

    private:
        GLFWwindow *m_window;
        WindowSpecification m_spec;
    };

}