#pragma once

#include "core/layer.h"
#include "core/image.h"

#include "audio/audiofile.h"

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

        std::shared_ptr<AudioFile> m_audioFile = nullptr;
    };
}