#pragma once

#include "core/layer.h"

#include "audio/audiodevice.h"

#include <string>
#include <map>

namespace SoundStation {
    class AudioDeviceManagerLayer : public Layer {
    public:
        AudioDeviceManagerLayer();
        ~AudioDeviceManagerLayer() override = default;

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep step) override;
        void onUIRender() override;

        std::shared_ptr<AudioDevice> getAudioDevice() const { return m_audioDevice; }

    private:
        std::shared_ptr<AudioDevice> m_audioDevice = nullptr;
        std::map<uint32_t,std::string> m_availableDevices;
        uint32_t m_selectedDevice = -1;
    };
}