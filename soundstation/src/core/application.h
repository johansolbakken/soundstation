#pragma once

#include "core/layerstack.h"
#include "core/window.h"

#include <memory>

namespace SoundStation
{
    class Application
    {
    public:
        Application();
        ~Application();

        static Application& instance();

        void run();

        std::shared_ptr<Window> window() { return m_window; }

    private:
        bool m_running = true;
        LayerStack m_layerStack;
        std::shared_ptr<Window> m_window = nullptr;
    };
}