#pragma once

#include "core/layer.h"

#include "audio/audiodevice.h"

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
    };
}