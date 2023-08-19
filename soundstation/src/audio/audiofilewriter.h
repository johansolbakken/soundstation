#pragma once

#include <string>

#include "audio/audiobuffer.h"

namespace SoundStation
{

    enum class AudioFileFormat
    {
        Unknown,
        MP3,
        Aiff,
    };

    class AudioFileWriter
    {
    public:
        static void write(const std::string& filename, const std::shared_ptr<AudioBuffer>& buffer, AudioFileFormat format);
    };
}