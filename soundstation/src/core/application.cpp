#include "application.h"

#include "core/log.h"

namespace SoundStation
{
    Application::Application()
    {
        SS_LOG_INFO("SoundStation is awake!");
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        while (m_running) {

        }
    }
}