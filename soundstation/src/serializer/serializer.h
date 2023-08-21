#pragma once

#include "core/project.h"

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

        std::vector<std::shared_ptr<AudioFile>> audioFiles() const;
        void setAudioFiles(const std::vector<std::shared_ptr<AudioFile>> &audioFiles);

        const Project &project() const { return m_project; }
        void setProject(const Project &project) { m_project = project; }

    private:
        std::vector<std::string> m_audioFiles;
        Project m_project;
    };

}