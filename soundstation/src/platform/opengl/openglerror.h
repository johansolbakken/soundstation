#pragma once

#include <glad/glad.h>

#include "core/assert.h"

#define GL_CLEAR_ERROR() while (glGetError() != GL_NO_ERROR)

#define GLLogCall(x, file, line)                                                         \
    GL_CLEAR_ERROR();                                                                    \
    x;                                                                                   \
    while (GLenum error = glGetError())                                                  \
    {                                                                                    \
        SS_LOG_ERROR(fmt::format("OpenGL Error ({}): {} {}:{}", error, #x, file, line)); \
    }

#define GL_CALL(x) GLLogCall(x, __FILE__, __LINE__)