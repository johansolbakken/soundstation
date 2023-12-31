#pragma once

namespace SoundStation
{
    enum class AudioBufferFormat
    {
        Unknown,
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
            size_t channels);
        ~AudioBuffer();

        void setData(float *data) { m_data = data; }

        const float *data() const { return m_data; }
        float* data() { return m_data; }
        float sampleRate() const { return m_sampleRate; }
        AudioBufferFormat format() const { return m_format; }
        size_t channels() const { return m_channels; }
        size_t size() const { return m_size; }

        size_t frames() const { return m_size / m_channels; }
        double duration() const { return double(m_size) / double(m_sampleRate) / double(m_channels); }

        std::shared_ptr<AudioBuffer> convertSampleRate(float newSampleRate) const;

        static std::shared_ptr<AudioBuffer> create(
            float *data,
            size_t size,
            float sampleRate,
            AudioBufferFormat format,
            size_t channels);

    private:
        float *m_data = nullptr;
        size_t m_size = 0;
        float m_sampleRate = 0.0f;
        AudioBufferFormat m_format = AudioBufferFormat::Unknown;
        size_t m_channels = 0;
    };
};
