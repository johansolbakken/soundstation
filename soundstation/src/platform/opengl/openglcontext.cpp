#include "openglcontext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/assert.h"

#include "platform/opengl/openglerror.h"

namespace SoundStation
{
    static uint32_t s_globalVAO = 0;

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(glfwGetCurrentContext());
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SS_ASSERT(status, "Failed to initialize Glad!");

        GL_CALL(glEnable(GL_BLEND));

        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        GL_CALL(glEnable(GL_DEPTH_TEST));

        GL_CALL(glGenVertexArrays(1, &s_globalVAO));
        GL_CALL(glBindVertexArray(s_globalVAO));
    }

    void OpenGLContext::shutdown()
    {
        GL_CALL(glDeleteVertexArrays(1, &s_globalVAO));
    }
}