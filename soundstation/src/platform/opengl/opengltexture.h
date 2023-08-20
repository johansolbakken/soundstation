#pragma once

#include "renderer/texture.h"

namespace SoundStation
{
    class OpenGLTexture : public Texture
    {
    public:
        OpenGLTexture();
        ~OpenGLTexture() override;

        void bind() override;
        void unbind() override;

        void load(const std::string &path) override;

        void resize(uint32_t width, uint32_t height) override;
        void setData(void *data, uint32_t size) override;
        void setFormat(TextureFormat format) override;

        uint32_t rendererId() const override { return m_rendererID; }

        uint32_t width() const override { return m_width; }
        uint32_t height() const override { return m_height; }
        TextureFormat format() const override { return m_format; }

    private:
        uint32_t m_rendererID = 0;
        uint32_t m_width = 0;
        uint32_t m_height = 0;
        TextureFormat m_format = TextureFormat::None;
    };
}