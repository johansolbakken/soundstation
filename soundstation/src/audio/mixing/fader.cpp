#include "pch.h"
#include "fader.h"

namespace SoundStation
{
    Fader::Fader(float level)
        : m_level(level)
    {
    }

    Fader::~Fader()
    {
    }

    void Fader::setLevel(float level)
    {
        m_level = level;
    }

    float Fader::level() const
    {
        return m_level;
    }

    void Fader::process(float *buffer, int numSamples)
    {
        auto data = reinterpret_cast<float(*)[2]>(buffer);
        for (int i = 0; i < numSamples; ++i)
        {
            data[i][0] *= m_level;
            data[i][1] *= m_level;
        }
    }

    std::shared_ptr<Fader> Fader::create(float level)
    {
        return std::make_shared<Fader>(level);
    }
}