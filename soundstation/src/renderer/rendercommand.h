#pragma once

#include <glm/glm.hpp>

namespace SoundStation {
    class RenderCommand {
    public:
        static void setClearColor(const glm::vec4& color);
        static void clear();
        static void drawArrays(uint32_t count);
    };
}