#pragma once

#include "core/layerstack.h"
#include "core/window.h"

#include "imgui/imguilayer.h"

#include "layers/audiodevicemanagerlayer.h"

#include <memory>

namespace SoundStation
{
    class Application
    {
    public:
        Application();
        ~Application();

        static Application &instance();

        void run();

        std::shared_ptr<Window> window() { return m_window; }

        void close();

        std::shared_ptr<AudioDevice> currentAudioDevice() const { return m_audioDeviceManagerLayer->getAudioDevice(); }

    private:
        bool m_running = true;
        LayerStack m_layerStack;
        std::shared_ptr<Window> m_window = nullptr;
        ImGuiLayer *m_imguiLayer = nullptr;
        size_t m_lastTime = 0;

        AudioDeviceManagerLayer* m_audioDeviceManagerLayer = nullptr;
    };
}