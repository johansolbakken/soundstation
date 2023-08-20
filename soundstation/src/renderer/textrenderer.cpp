#include "textrenderer.h"

#include "renderer/shader.h"
#include "renderer/texture.h"

namespace SoundStation
{

    struct TextRendererData
    {
        std::shared_ptr<Shader> textShader;
    };

    static TextRendererData *s_data = nullptr;

    void TextRenderer::init()
    {
        s_data = new TextRendererData();
        s_data->textShader = Shader::create("assets/shaders/text.vert", "assets/shaders/text.frag");
    }

    void TextRenderer::shutdown()
    {
        delete s_data;
    }

    void TextRenderer::drawText(const std::string &text, float fontSize, const glm::vec3 &color, const glm::vec2 &position)
    {
        s_data->textShader->bind();
        //s_data->textShader->setVec3("u_textColor", color);
    }
}