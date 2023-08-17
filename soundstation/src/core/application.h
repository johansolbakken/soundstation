#pragma once

#include "core/layerstack.h"

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
    };
}