#pragma once

#include <cstdint>
#include <chrono>

namespace SoundStation
{
    class Time
    {
    public:
        static float systemTimeSeconds();
        static float systemTimeMilliseconds();
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