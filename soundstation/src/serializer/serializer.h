#pragma once

#include "audio/audiofile.h"

#include <vector>

namespace SoundStation
{

    class Serializer
    {
    public:
        Serializer() = default;
        ~Serializer() = default;

        void serialize(const std::string &filename);
        void deserialize(const std::string &filename);

        const std::vector<std::shared_ptr<AudioFile>> &audioFiles() const { return m_audioFiles; }
        void setAudioFiles(const std::vector<std::shared_ptr<AudioFile>> &audioFiles) { m_audioFiles = audioFiles; }

    private:
        std::vector<std::shared_ptr<AudioFile>> m_audioFiles;
    };

}