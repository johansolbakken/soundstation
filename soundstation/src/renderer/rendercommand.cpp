#include "rendercommand.h"

#include "platform/opengl/openglrenderapi.h"

namespace SoundStation
{
    void RenderCommand::setClearColor(const glm::vec4& color)
    {
        OpenGLRenderAPI::setClearColor(color);
    }

    void RenderCommand::clear()
    {
        OpenGLRenderAPI::clear();
    }

    void RenderCommand::drawArrays(uint32_t count)
    {
        OpenGLRenderAPI::drawArrays(count);
    }

    void RenderCommand::drawIndexed(uint32_t count)
    {
        OpenGLRenderAPI::drawIndexed(count);
    }
}