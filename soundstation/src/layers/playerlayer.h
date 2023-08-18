#pragma once

#include "core/layer.h"

#include "core/image.h"

#include "audio/audio.h"
#include "audio/audiobuffer.h"
#include "audio/audiodevice.h"

namespace SoundStation
{
    class PlayerLayer : public Layer
    {
    public:
        PlayerLayer();
        ~PlayerLayer() override;

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep step) override;
        void onUIRender() override;

    private:
        bool m_playing = false;
        float m_cursor = 0.0;

        Image m_noteImage;
        Image m_playImage;
        Image m_pauseImage;

        std::shared_ptr<Audio> m_audio = nullptr;
        std::shared_ptr<AudioBuffer> m_audioBuffer = nullptr;
        std::shared_ptr<AudioDevice> m_audioDevice = nullptr;
    };
}