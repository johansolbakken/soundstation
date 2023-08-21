#pragma once

namespace SoundStation
{
    class Fader
    {
    public:
        Fader(float level = 1.0f);
        ~Fader();

        void setLevel(float level);
        float level() const;

        void process(float *buffer, int numSamples);

        static std::shared_ptr<Fader> create(float level = 1.0f);

    private:
        float m_level = 1.0f;
    };
}