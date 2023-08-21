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
        ~PlayerLayer() override = default;

        void onUIRender() override;

        void setAudioFile(const std::shared_ptr<AudioFile>& file);
        void clearAudioFile();

        static std::string staticName() { return "PlayerLayer"; }

    private:
        void play();
        void pause();

    private:
        bool m_seeking = false;
        double m_seekPosition = 0.0;

        Image m_noteImage;
        Image m_playImage;
        Image m_pauseImage;

        std::shared_ptr<AudioFile> m_audioFile = nullptr;
    };
}