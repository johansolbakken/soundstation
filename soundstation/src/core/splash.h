#pragma once

#include "core/window.h"

namespace SoundStation
{

    class SplashScreen
    {
    public:
        SplashScreen();

    private:
        std::unique_ptr<Window> m_window;
    };

}