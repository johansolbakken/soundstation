#pragma once

#include "core/layer.h"

#include "audio/audiobuffer.h"
#include "audio/audiofile.h"

#include "audio/mixing/fader.h"

namespace SoundStation
{
    class MixerLayer : public Layer
    {
    public:
        MixerLayer();
        ~MixerLayer() override = default;

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep t) override;
        void onUIRender() override;

        static std::string staticName() { return "MixerLayer"; }

        void setAudioFile(std::shared_ptr<AudioFile> audioFile) { m_audioFile = audioFile; }

    private:
        void renderFader(const std::string &name, std::shared_ptr<Fader> fader);

        void audioCallback(float *data, uint32_t frames, uint32_t channels, float sampleRate);

    private:
        std::shared_ptr<AudioBuffer> m_outputBuffer;
        std::shared_ptr<Fader> m_fader;
        std::shared_ptr<AudioFile> m_audioFile;
    };
}