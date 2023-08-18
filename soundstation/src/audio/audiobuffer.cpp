#include "audiobuffer.h"

namespace SoundStation
{
    AudioBuffer::AudioBuffer(float *data, float sampleRate, AudioBufferFormat format, size_t channels)
        : m_data(data), m_sampleRate(sampleRate), m_format(format), m_channels(channels)
    {

    }

    AudioBuffer::~AudioBuffer()
    {
        
    }
}