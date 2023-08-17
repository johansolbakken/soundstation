#include "application.h"

#include "core/log.h"

#include "renderer/renderer.h"

namespace SoundStation
{
    Application::Application()
    {
        m_window = std::make_shared<Window>(WindowSpecification{"SoundStation", 1280, 720});

        Renderer::init();

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