#include "application.h"

#include "core/log.h"
#include "core/assert.h"

#include "renderer/renderer.h"

#include <imgui.h>

#include "layers/playerlayer.h"
#include "layers/audiodevicemanagerlayer.h"

namespace SoundStation
{
    static Application *s_instance = nullptr;

    Application::Application()
    {
        SS_ASSERT(!s_instance, "Application instance already exists!");
        s_instance = this;

        m_window = std::make_shared<Window>(WindowSpecification{"SoundStation", 1280, 720});

        Renderer::init();

        m_imguiLayer = new ImGuiLayer();
        m_layerStack.pushOverlay(m_imguiLayer);

        m_layerStack.pushLayer(new PlayerLayer());
        m_layerStack.pushLayer(new AudioDeviceManagerLayer());

        SS_LOG_INFO("SoundStation is awake!");
    }

    Application::~Application()
    {
        Renderer::shutdown();
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
            RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
            RenderCommand::clear();

            for (Layer *layer : m_layerStack)
            {
                layer->onUpdate();
            }

            m_imguiLayer->begin();

            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

            for (Layer *layer : m_layerStack)
            {
                layer->onUIRender();
            }

            m_imguiLayer->end();

            m_window->onUpdate();
        }
    }

    void Application::close()
    {
        m_running = false;
    }
}