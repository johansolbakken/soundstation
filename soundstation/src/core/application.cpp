#include "application.h"

#include "core/log.h"

namespace SoundStation
{
    Application::Application()
    {
        m_window = std::make_unique<Window>(WindowSpecification{"SoundStation", 1280, 720});

        SS_LOG_INFO("SoundStation is awake!");
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        while (m_running)
        {
            for (Layer *layer : m_layerStack)
            {
                layer->onUpdate();
            }

            m_window->onUpdate();
        }
    }
}