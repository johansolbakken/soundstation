#pragma once

#include "core/layerstack.h"
#include "core/window.h"
#include "core/project.h"

#include "imgui/imguilayer.h"

#include "layers/audiodevicemanagerlayer.h"
#include "layers/projectlayer.h"

#include <memory>

template <typename T>
concept HasStaticName = requires {
    {
        T::staticName()
    } -> std::convertible_to<std::string>;
};

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

        std::shared_ptr<AudioDevice> currentAudioDevice() const { return m_audioDeviceManagerLayer->audioDevice(); }
        const Project &currentProject() const { return m_projectLayer->project(); }

        void pushLayer(Layer *layer);

        Layer *getLayerPtr(const std::string &name);

        template <typename T>
            requires HasStaticName<T>
        static T *getLayer()
        {
            return static_cast<T *>(instance().getLayerPtr(T::staticName()));
        }

    private:
        bool m_running = true;
        LayerStack m_layerStack;
        std::shared_ptr<Window> m_window = nullptr;
        ImGuiLayer *m_imguiLayer = nullptr;
        size_t m_lastTime = 0;

        AudioDeviceManagerLayer *m_audioDeviceManagerLayer = nullptr;
        ProjectLayer *m_projectLayer = nullptr;
    };
}