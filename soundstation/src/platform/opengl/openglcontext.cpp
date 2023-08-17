#include "openglcontext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/assert.h"

namespace SoundStation
{
    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(glfwGetCurrentContext());
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SS_ASSERT(status, "Failed to initialize Glad!");
    }
}