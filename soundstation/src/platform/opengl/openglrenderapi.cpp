#include "openglrenderapi.h"

#include <glad/glad.h>

namespace SoundStation
{
    void OpenGLRenderAPI::setClearColor(const glm::vec4 &color)
    {
        glClearColor(color.r,
                     color.g,
                     color.b,
                     color.a);
    }

    void OpenGLRenderAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}