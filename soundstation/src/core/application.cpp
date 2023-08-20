#include "application.h"

#include "core/log.h"
#include "core/assert.h"
#include "core/time.h"
#include "core/splash.h"

#include "renderer/renderer.h"

#include <imgui.h>

#include "layers/playerlayer.h"
#include "layers/audiodevicemanagerlayer.h"
#include "layers/filereaderwriterlayer.h"
#include "layers/toolbarlayer.h"
#include "layers/audiolibrarylayer.h"
#include "layers/menubarlayer.h"

namespace SoundStation
{
    static Application *s_instance = nullptr;

    Application::Application()
    {
        SS_ASSERT(!s_instance, "Application instance already exists!");
        s_instance = this;

        Window::initSubsystem();
        
        {
            SplashScreen splash;
        }

        m_window = std::make_shared<Window>(WindowSpecification{"SoundStation", 1280, 720});
        Renderer::init();

        m_imguiLayer = new ImGuiLayer();
        m_layerStack.pushOverlay(m_imguiLayer);
        m_imguiLayer->onAttach();

        // system layers
        pushLayer(new ToolbarLayer());

        m_audioDeviceManagerLayer = new AudioDeviceManagerLayer();
        pushLayer(m_audioDeviceManagerLayer);

        pushLayer(new PlayerLayer());
        pushLayer(new FileReaderWriterLayer());
        pushLayer(new AudioLibraryLayer());
        pushLayer(new MenuBarLayer());
        // system layers

        SS_LOG_INFO("SoundStation is awake!");
    }

    Application::~Application()
    {
        Renderer::shutdown();
        Window::shutdownSubsystem();
    }

    Application &Application::instance()
    {
        SS_ASSERT(s_instance, "Application instance is null!");
        return *s_instance;
    }

    void Application::run()
    {
        m_window->show();

        while (m_running)
        {
            size_t current = Time::systemTimeMilliseconds();
            Timestep timestep = (current - m_lastTime) * 0.001f;
            m_lastTime = current;

            RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
            RenderCommand::clear();

            for (Layer *layer : m_layerStack)
            {
                layer->onUpdate(timestep);
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

    void Application::pushLayer(Layer *layer)
    {
        m_layerStack.pushLayer(layer);
        layer->onAttach();
    }

    Layer *Application::getLayer(const std::string &name)
    {
        for (auto layer : m_layerStack)
        {
            if (layer->name() == name)
            {
                return layer;
            }
        }

        return nullptr;
    }
}