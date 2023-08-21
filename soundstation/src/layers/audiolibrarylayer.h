#pragma once

#include "core/layer.h"

#include "audio/audiofile.h"

#include <vector>

namespace SoundStation
{

    class AudioLibraryLayer : public Layer
    {
    public:
        AudioLibraryLayer();
        ~AudioLibraryLayer() override = default;

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep t) override;
        void onUIRender() override;

        std::vector<std::shared_ptr<AudioFile>> audioFiles() const { return m_audioFiles; }
        void setAudioFiles(const std::vector<std::shared_ptr<AudioFile>> &audioFiles) { m_audioFiles = audioFiles; }

    private:
        uint32_t m_cachedSampleRate = 0;
        std::vector<std::shared_ptr<AudioFile>> m_audioFiles;
    };
}