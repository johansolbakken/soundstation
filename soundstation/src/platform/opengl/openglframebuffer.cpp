#include "pch.h"
#include "openglframebuffer.h"

#include <glad/glad.h>

#include "platform/opengl/openglerror.h"

namespace SoundStation
{
    OpenGLFramebuffer::OpenGLFramebuffer(uint32_t width, uint32_t height)
        : m_width(width), m_height(height)
    {
        GL_CALL(glGenFramebuffers(1, &m_rendererID));
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID));

        GL_CALL(glGenTextures(1, &m_colorAttachment));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_colorAttachment));
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
        GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0));

        GL_CALL(glGenRenderbuffers(1, &m_depthAttachment));
        GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment));
        GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
        GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment));

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        SS_ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        GL_CALL(glDeleteFramebuffers(1, &m_rendererID));
        GL_CALL(glDeleteTextures(1, &m_colorAttachment));
        GL_CALL(glDeleteRenderbuffers(1, &m_depthAttachment));
    }

    void OpenGLFramebuffer::bind()
    {
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID));
    }

    void OpenGLFramebuffer::unbind()
    {
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    void OpenGLFramebuffer::resize(uint32_t width, uint32_t height)
    {
        m_width = width;
        m_height = height;

        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_colorAttachment));
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

        GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment));
        GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        SS_ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    std::shared_ptr<Framebuffer> Framebuffer::create(uint32_t width, uint32_t height)
    {
        return std::make_shared<OpenGLFramebuffer>(width, height);
    }
}