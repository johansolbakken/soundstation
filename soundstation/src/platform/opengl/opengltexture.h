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

        uint32_t rendererId() const override { return m_rendererID; }

        uint32_t width() const override { return m_width; }
        uint32_t height() const override { return m_height; }

    private:
        uint32_t m_rendererID = 0;
        uint32_t m_width = 0;
        uint32_t m_height = 0;
    };
}