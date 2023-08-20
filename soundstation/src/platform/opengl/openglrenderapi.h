#pragma once

#include <glm/glm.hpp>

namespace SoundStation
{
    class OpenGLRenderAPI
    {
    public:
        static void setClearColor(const glm::vec4& color);
        static void clear();
        
        static void drawArrays(uint32_t count);
        static void drawIndexed(uint32_t count);
    };
}