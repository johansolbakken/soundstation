#include "time.h"

#include <chrono>

namespace SoundStation
{
    float Time::systemTimeSeconds()
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    float Time::systemTimeMilliseconds()
    {
        return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
}