#pragma once

namespace SoundStation
{
    class Time
    {
    public:
        static size_t systemTimeSeconds();
        static size_t systemTimeMilliseconds();
    };

    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
            : m_time(time)
        {
        }

        operator float() const { return m_time; }

        float seconds() const { return m_time; }
        float milliseconds() const { return m_time * 1000.0f; }

    private:
        float m_time;
    };
}