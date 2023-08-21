#include "pch.h"
#include "fader.h"

namespace SoundStation
{
    Fader::Fader(float gain)
        : m_gain(gain)
    {
    }

    Fader::~Fader()
    {
    }

    void Fader::setGain(float gain)
    {
        m_gain = gain;
    }

    float Fader::gain() const
    {
        return m_gain;
    }

    void Fader::process(float *buffer, int numSamples)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            buffer[i] *= m_gain;
        }
    }

    std::shared_ptr<Fader> Fader::create(float gain)
    {
        return std::make_shared<Fader>(gain);
    }
}