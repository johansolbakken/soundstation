#include "application.h"

#include "core/log.h"
#include "core/assert.h"

#include "renderer/renderer.h"

namespace SoundStation
{
    static Application *s_instance = nullptr;

    Application::Application()
    {
        SS_ASSERT(!s_instance, "Application instance already exists!");

        m_window = std::make_shared<Window>(WindowSpecification{"SoundStation", 1280, 720});

        Renderer::init();

        SS_LOG_INFO("SoundStation is awake!");
        s_instance = this;
    }

    Application::~Application()
    {
    }

    Application& Application::instance() {
        SS_ASSERT(s_instance, "Application instance is null!");
        return *s_instance;
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