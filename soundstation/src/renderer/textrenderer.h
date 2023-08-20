#pragma once

#include <string>

#include <glm/glm.hpp>

namespace SoundStation {
    class TextRenderer {
    public:
        static void init();
        static void shutdown();

        static void drawText(const std::string &text, float fontSize, const glm::vec3 &color, const glm::vec2 &position);
    };
}