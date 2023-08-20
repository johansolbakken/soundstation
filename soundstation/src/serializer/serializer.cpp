#include "serializer.h"

#include <nlohmann/json.hpp>

#include <fstream>

namespace SoundStation
{
    void Serializer::serialize(const std::string &filename)
    {
        nlohmann::json json;
        json["title"] = "Sound Station Project";
        json["version"] = "0.0.1";
        json["audioFiles"] = nlohmann::json::array();

        for (auto &audioFile : m_audioFiles)
        {
            nlohmann::json audioFileJson;
            audioFileJson["filename"] = audioFile->filename();
            json["audioFiles"].push_back(audioFileJson);
        }

        std::ofstream file(filename);
        file << json.dump(4);
        file.close();
    }

    void Serializer::deserialize(const std::string &filename)
    {
        }
}