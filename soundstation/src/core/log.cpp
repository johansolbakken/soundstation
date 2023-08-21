#include "pch.h"
#include "log.h"

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>

namespace SoundStation
{
    void Log::debug(const std::string& message)
    {
        log(fmt::color::gray, "[DEBUG]", message);
    }

    void Log::info(const std::string& message)
    {
        log(fmt::color::blue, "[INFO]", message);
    }

    void Log::warn(const std::string& message)
    {
        log(fmt::color::yellow, "[WARN]", message);
    }

    void Log::error(const std::string& message)
    {
        log(fmt::color::red, "[ERROR]", message);
    }

    void Log::log(fmt::color color, const char *level, const std::string& message)
    {
        fmt::print(fg(color), "{} {}\n", level, message);
    }
}