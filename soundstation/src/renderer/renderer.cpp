#include "pch.h"
#include "renderer.h"

#include "platform/opengl/openglcontext.h"

namespace SoundStation
{
    void Renderer::init()
    {
        OpenGLContext::init();
        TextRenderer::init();
    }
    void Renderer::shutdown()
    {
        TextRenderer::shutdown();
        OpenGLContext::shutdown();
    }
}