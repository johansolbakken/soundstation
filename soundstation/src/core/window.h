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
        bool showMenuBar = true;
    };

    class Window
    {
    public:
        Window(const WindowSpecification &spec);
        ~Window();

        void onUpdate();

        void *nativeWindow() const { return m_window; }

        uint32_t width() const { return m_spec.width; }
        uint32_t height() const { return m_spec.height; }
        float x() const;
        float y() const;

        void show();

        static void initSubsystem();
        static void shutdownSubsystem();

    private:
        GLFWwindow *m_window;
        WindowSpecification m_spec;
    };

}