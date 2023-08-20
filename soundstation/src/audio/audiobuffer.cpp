#include "audiobuffer.h"

#include "core/log.h"

namespace SoundStation
{
    AudioBuffer::AudioBuffer(float *data, size_t size, float sampleRate, AudioBufferFormat format, size_t channels)
        : m_data(data), m_size(size), m_sampleRate(sampleRate), m_format(format), m_channels(channels)
    {
    }

    AudioBuffer::~AudioBuffer()
    {
        delete[] m_data;
    }

    std::shared_ptr<AudioBuffer> AudioBuffer::convertSampleRate(float newSampleRate) const
    {
        if (m_sampleRate == newSampleRate)
        {
            float *data = new float[m_size];
            size_t size = m_size;
            float sampleRate = m_sampleRate;
            AudioBufferFormat format = m_format;
            size_t channels = m_channels;
            memcpy(data, m_data, m_size * sizeof(float));
            return std::make_shared<AudioBuffer>(data, size, sampleRate, format, channels);
        }

        SS_LOG_INFO(fmt::format("Converting sample rate from {} to {}", m_sampleRate, newSampleRate));

        float ratio = m_sampleRate / newSampleRate;
        size_t newSize = size_t(m_size / ratio);
        float *newData = new float[newSize];
        for (size_t i = 0; i < newSize; i++)
        {
            size_t oldIndex = size_t(i * ratio);
            newData[i] = m_data[oldIndex];
        }

        return std::make_shared<AudioBuffer>(newData, newSize, newSampleRate, m_format, m_channels);
    }
}