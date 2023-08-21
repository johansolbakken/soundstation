#include "pch.h"
#include "textrenderer.h"

#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/rendercommand.h"
#include "renderer/buffer.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace SoundStation
{

    struct TextRendererData
    {
        std::shared_ptr<Shader> textShader;
        FT_Library ft;
        std::map<std::string, FT_Face> faces;
    };

    static TextRendererData *s_data = nullptr;

    void TextRenderer::init()
    {
        s_data = new TextRendererData();
        s_data->textShader = Shader::create("assets/shaders/text.vert", "assets/shaders/text.frag");
        if (FT_Init_FreeType(&s_data->ft))
        {
            SS_LOG_ERROR("Could not init FreeType Library");
        }
        {
            FT_Face face;
            if (FT_New_Face(s_data->ft, "assets/fonts/Roboto/Roboto-Regular.ttf", 0, &face))
            {
                SS_LOG_ERROR("Failed to load font");
            }
            FT_Set_Pixel_Sizes(face, 0, 48);
            s_data->faces["Roboto-regular-48"] = face;
        }
    }

    void TextRenderer::shutdown()
    {
        for (auto &face : s_data->faces)
        {
            FT_Done_Face(face.second);
        }
        FT_Done_FreeType(s_data->ft);
        delete s_data;
    }

    void TextRenderer::drawText(const std::string &text, float fontSize, const glm::vec3 &color, const glm::vec2 &position)
    {
        s_data->textShader->bind();
        s_data->textShader->setVec3("u_textColor", color);

        FT_Face face = s_data->faces["Roboto-regular-48"];

        for (char c : text)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                SS_LOG_ERROR("Failed to load glyph");
                continue;
            }

            auto texture = Texture::create();
            texture->setFormat(TextureFormat::Red);
            texture->resize(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            texture->setData(face->glyph->bitmap.buffer, face->glyph->bitmap.width * face->glyph->bitmap.rows);

            float x = position.x + face->glyph->bitmap_left * fontSize;
            float y = position.y - (face->glyph->bitmap.rows - face->glyph->bitmap_top) * fontSize;
            float w = face->glyph->bitmap.width * fontSize;
            float h = face->glyph->bitmap.rows * fontSize;

            float vertices[6][3 + 2] = {
                {x, y + h, 0.0f, 0.0f, 0.0f},
                {x, y, 0.0f, 0.0f, 1.0f},
                {x + w, y, 0.0f, 1.0f, 1.0f},

                {x, y + h, 0.0f, 0.0f, 0.0f},
                {x + w, y, 0.0f, 1.0f, 1.0f},
                {x + w, y + h, 0.0f, 1.0f, 0.0f}
            };

            BufferLayout layout = {{{BufferDataType::Float3}, {BufferDataType::Float2}}};

            auto vertexBuffer = Buffer::create(BufferType::Vertex);
            vertexBuffer->bind();
            vertexBuffer->setData(vertices, sizeof(vertices));
            vertexBuffer->setLayout(layout);

            texture->bind();
            s_data->textShader->setInt("u_texture", 0);

            RenderCommand::drawArrays(6);

            vertexBuffer->unbind();
        }
    }
}