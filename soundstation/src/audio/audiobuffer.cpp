#include "audiobuffer.h"

namespace SoundStation
{
    AudioBuffer::AudioBuffer(float *data, size_t size, float sampleRate, AudioBufferFormat format, size_t channels)
        : m_data(data), m_size(size), m_sampleRate(sampleRate), m_format(format), m_channels(channels)
    {

    }

    AudioBuffer::~AudioBuffer()
    {
        
    }
}