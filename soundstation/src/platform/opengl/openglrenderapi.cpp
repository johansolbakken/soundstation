#include "openglrenderapi.h"

#include <glad/glad.h>

#include "platform/opengl/openglerror.h"

namespace SoundStation
{
    void OpenGLRenderAPI::setClearColor(const glm::vec4 &color)
    {
        GL_CALL(glClearColor(color.r,
                             color.g,
                             color.b,
                             color.a));
    }

    void OpenGLRenderAPI::clear()
    {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
}