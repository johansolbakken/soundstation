#pragma once

namespace SoundStation
{
    class Fader
    {
    public:
        Fader(float gain = 1.0f);
        ~Fader();

        void setGain(float gain);
        float gain() const;

        void process(float *buffer, int numSamples);

        static std::shared_ptr<Fader> create(float gain = 1.0f);

    private:
        float m_gain = 1.0f;
    };
}