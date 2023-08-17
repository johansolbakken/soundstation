#pragma once

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
    };
}