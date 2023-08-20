#pragma once

#include "core/window.h"

namespace SoundStation
{
    class SplashScreen
    {
    public:
        SplashScreen();
        void run();

        std::shared_ptr<Window> window() const { return m_window; }

    private:
        std::shared_ptr<Window> m_window;
    };
}