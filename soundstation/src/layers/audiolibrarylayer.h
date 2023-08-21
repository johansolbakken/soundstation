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

        void onUIRender() override;

        std::vector<std::shared_ptr<AudioFile>> audioFiles() const { return m_audioFiles; }
        void setAudioFiles(const std::vector<std::shared_ptr<AudioFile>> &audioFiles) { m_audioFiles = audioFiles; }
        void clearAudioFiles() { m_audioFiles.clear(); }

        static std::string staticName() { return "AudioLibraryLayer"; }

    private:
        std::vector<std::shared_ptr<AudioFile>> m_audioFiles;
    };
}