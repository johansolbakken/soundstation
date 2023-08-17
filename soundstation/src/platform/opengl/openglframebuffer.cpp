#include "openglframebuffer.h"

#include <glad/glad.h>

namespace SoundStation
{
    OpenGLFramebuffer::OpenGLFramebuffer(uint32_t width, uint32_t height)
        : m_width(width), m_height(height)
    {
        glGenFramebuffers(1, &m_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

        glGenTextures(1, &m_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

        glGenRenderbuffers(1, &m_depthAttachment);
        glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OpenGLFramebuffer::~OpenGLFramebuffer() override
    {
        glDeleteFramebuffers(1, &m_rendererID);
        glDeleteTextures(1, &m_colorAttachment);
        glDeleteRenderbuffers(1, &m_depthAttachment);
    }

    void OpenGLFramebuffer::bind() override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
    }

    void OpenGLFramebuffer::unbind() override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::resize(uint32_t width, uint32_t height) override
    {
        m_width = width;
        m_height = height;

        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    }

    std::shared_ptr<Framebuffer> Framebuffer::create(uint32_t width, uint32_t height)
    {
        return std::make_shared<OpenGLFramebuffer>(width, height);
    }
}