#pragma once

#include <string>

#include "audio/audiobuffer.h"

namespace SoundStation
{
    class AudioFile
    {
    public:
        AudioFile(const std::string &filename);
        ~AudioFile();

        std::shared_ptr<AudioBuffer> audioBuffer() const { return m_buffer; }

    private:    
        std::string m_filename;
        std::shared_ptr<AudioBuffer> m_buffer;
    };
}