#include "renderer.h" 

#include "platform/opengl/openglcontext.h"

namespace SoundStation {
    void Renderer::init() {
        OpenGLContext::init();
    }
    void Renderer::shutdown() {
        OpenGLContext::shutdown();
    }
}