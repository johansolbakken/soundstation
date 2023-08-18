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

    private:
        std::shared_ptr<AudioDevice> m_audioDevice = nullptr;
    };
}