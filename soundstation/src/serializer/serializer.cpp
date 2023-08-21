#include "pch.h"
#include "serializer.h"

#include <nlohmann/json.hpp>

namespace SoundStation
{
    void Serializer::serialize(const std::string &filename)
    {
        nlohmann::json json;
        json["title"] = "Sound Station Project";
        json["version"] = "0.0.1";

        json["project"]["name"] = m_project.name();
        json["project"]["sampleRate"] = m_project.sampleRate();

        json["audioFiles"] = nlohmann::json::array();
        for (auto &audioFile : m_audioFiles)
        {
            nlohmann::json audioFileJson;
            audioFileJson["filename"] = audioFile;
            json["audioFiles"].push_back(audioFileJson);
        }

        std::ofstream file(filename);
        file << json.dump(4);
        file.close();
    }

    void Serializer::deserialize(const std::string &filename)
    {
        std::ifstream file(filename);
        nlohmann::json json;
        file >> json;
        file.close();

        m_project.setName(json["project"]["name"]);
        m_project.setPath(filename);
        m_project.setSampleRate(json["project"]["sampleRate"]);

        m_audioFiles.clear();
        for (auto &audioFile : json["audioFiles"])
            m_audioFiles.push_back(audioFile["filename"]);
    }

    std::vector<std::shared_ptr<AudioFile>> Serializer::audioFiles() const
    {
        std::vector<std::shared_ptr<AudioFile>> audioFiles;
        for (auto &audioFile : m_audioFiles)
            audioFiles.push_back(AudioFile::create(audioFile));
        return audioFiles;
    }

    void Serializer::setAudioFiles(const std::vector<std::shared_ptr<AudioFile>> &audioFiles)
    {
        m_audioFiles.clear();
        for (auto &audioFile : audioFiles)
            m_audioFiles.push_back(audioFile->filename());
    }
}