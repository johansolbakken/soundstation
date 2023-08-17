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

        void run();

    private:
        bool m_running = true;
        LayerStack m_layerStack;
        std::shared_ptr<Window> m_window = nullptr;
    };
}