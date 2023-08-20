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

        const std::string& filename() const { return m_filename; }

        static std::shared_ptr<AudioFile> create(const std::string &filename);

    private:    
        std::string m_filename;
        std::shared_ptr<AudioBuffer> m_buffer;
    };
}