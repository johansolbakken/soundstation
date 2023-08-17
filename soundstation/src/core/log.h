#pragma once

#include <fmt/color.h>

#include <string>

namespace SoundStation
{
    class Log
    {
    public:
        static void debug(const std::string& message);
        static void info(const std::string& message);
        static void warn(const std::string& message);
        static void error(const std::string& message);

    private:
        static void log(fmt::color color, const char *level, const std::string& message);
    };
}

#define SS_LOG_DEBUG(message) SoundStation::Log::debug(fmt::format("{}:{}: {}", __FILE__,__LINE__, message))
#define SS_LOG_INFO(message) SoundStation::Log::info(fmt::format("{}:{}: {}", __FILE__, __LINE__,message))
#define SS_LOG_WARN(message) SoundStation::Log::warn(fmt::format("{}:{}: {}", __FILE__, __LINE__,message))
#define SS_LOG_ERROR(message) SoundStation::Log::error(fmt::format("{}:{}: {}", __FILE__, __LINE__,message))