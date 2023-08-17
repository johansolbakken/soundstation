#pragma once

#include <glm/glm.hpp>

namespace SoundStation
{
    class OpenGLRenderAPI
    {
    public:
        static void setClearColor(const glm::vec4& color);
        static void clear();
    };
}