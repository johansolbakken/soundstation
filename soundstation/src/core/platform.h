#pragma once

#include <string>

namespace SoundStation {
    class Platform {
    public:
        static std::string openFile(const std::string &filter);
        static std::string saveFile(const std::string &filter);
    };
}