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
        void setAudioBuffer(const std::shared_ptr<AudioBuffer>& buffer) { m_buffer = buffer; }

        const std::string& filename() const { return m_filename; }
        double duration() const { return m_buffer->duration(); }
        size_t channels() const { return m_buffer->channels(); }
        float sampleRate() const { return m_buffer->sampleRate(); }

        static std::shared_ptr<AudioFile> create(const std::string &filename);

    private:    
        std::string m_filename;
        std::shared_ptr<AudioBuffer> m_buffer;
    };
}