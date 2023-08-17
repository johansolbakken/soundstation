#include "application.h"

#include "core/log.h"
#include "core/assert.h"

#include "renderer/renderer.h"

#include <imgui.h>

namespace SoundStation
{
    static Application *s_instance = nullptr;

    Application::Application()
    {
        SS_ASSERT(!s_instance, "Application instance already exists!");
        s_instance = this;

        m_window = std::make_shared<Window>(WindowSpecification{"SoundStation", 1280, 720});

        m_imguiLayer = new ImGuiLayer();
        m_layerStack.pushOverlay(m_imguiLayer);

        Renderer::init();

        SS_LOG_INFO("SoundStation is awake!");
    }

    Application::~Application()
    {
    }

    Application &Application::instance()
    {
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

            m_imguiLayer->begin();

            ImGui::Begin("Test");
            ImGui::Text("Hello World!");
            ImGui::End();

            m_imguiLayer->end();

            m_window->onUpdate();
        }
    }

    void Application::close()
    {
        m_running = false;
    }
}