#pragma once

#include <memory>

namespace SoundStation
{

    enum class AudioBufferFormat
    {
        Signed16Bit,
        Signed24Bit,
        Signed32Bit,
        Float32Bit
    };

    class AudioBuffer
    {
    public:
        AudioBuffer(
            float *data,
            size_t size,
            float sampleRate,
            AudioBufferFormat format,
            size_t channels
        );
        ~AudioBuffer();

        void setData(float *data) { m_data = data; }

        float *data() { return m_data; }
        float sampleRate() { return m_sampleRate; }
        AudioBufferFormat format() { return m_format; }
        size_t channels() { return m_channels; }
        size_t size() { return m_size; }

        // static std::shared_ptr<AudioBuffer> create(float *data, float sampleRate, AudioBufferFormat format, size_t channels, );

        // need size of data


    private:
        float *m_data = nullptr;
        size_t m_size = 0;
        float m_sampleRate = 0.0f;
        AudioBufferFormat m_format = AudioBufferFormat::Float32Bit;
        size_t m_channels = 0;
    };

};