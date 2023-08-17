#pragma once

#include <memory>

namespace SoundStation
{
    class OpenGLFramebuffer
    {
    public:
        OpenGLFramebuffer(uint32_t width, uint32_t height);
        ~OpenGLFramebuffer() override;

        void bind() override;
        void unbind() override;

        void resize(uint32_t width, uint32_t height) override;

        uint32_t colorAttachmentRendererID() const override { return m_colorAttachment; }
        uint32_t width() const override { return m_width; }
        uint32_t height() const override { return m_height; }

    private:
        uint32_t m_rendererID;
        uint32_t m_colorAttachment;
        uint32_t m_depthAttachment;
        uint32_t m_width;
        uint32_t m_height;
    };
}