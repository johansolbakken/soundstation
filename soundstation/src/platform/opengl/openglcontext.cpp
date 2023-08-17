#include "openglcontext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/assert.h"

#include "platform/opengl/openglerror.h"

namespace SoundStation
{
    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(glfwGetCurrentContext());
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SS_ASSERT(status, "Failed to initialize Glad!");

        GL_CALL(glEnable(GL_BLEND));
    }
}