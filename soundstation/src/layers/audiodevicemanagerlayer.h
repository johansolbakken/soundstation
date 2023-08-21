#pragma once

#include "core/layer.h"

#include "audio/audiodevice.h"
#include "audio/audiodevicelist.h"

namespace SoundStation {
    class AudioDeviceManagerLayer : public Layer {
    public:
        AudioDeviceManagerLayer();
        ~AudioDeviceManagerLayer() override = default;

        void onAttach() override;
        void onUIRender() override;

        std::shared_ptr<AudioDevice> getAudioDevice() const { return m_audioDevice; }

        void show() { m_open = true; }

    private:
        void selectOutputDevice(uint32_t id);

    private:
        std::shared_ptr<AudioDevice> m_audioDevice = nullptr;
        std::shared_ptr<AudioDeviceList> m_audioDeviceList = nullptr;
        uint32_t m_selectedOutputDevice = -1;
        uint32_t m_activeOutputDevice = -1;
        std::string m_activeOutputDeviceName = "";

        bool m_open = false;
    };
}