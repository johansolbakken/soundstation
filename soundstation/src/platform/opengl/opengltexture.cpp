#include "pch.h"
#include "opengltexture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "platform/opengl/openglerror.h"

namespace SoundStation
{
    OpenGLTexture::OpenGLTexture()
    {
        GL_CALL(glGenTextures(1, &m_rendererID));

        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }

    OpenGLTexture::~OpenGLTexture()
    {
        GL_CALL(glDeleteTextures(1, &m_rendererID));
    }

    void OpenGLTexture::bind()
    {
        GL_CALL(glActiveTexture(GL_TEXTURE0));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));
    }

    void OpenGLTexture::unbind()
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void OpenGLTexture::load(const std::string &path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (data)
        {
            GLenum format = 0;
            GLenum internalFormat = 0;
            if (channels == 1)
            {
                format = GL_RED;
                internalFormat = GL_RED;
                m_format = TextureFormat::Red;
            }
            else if (channels == 3)
            {
                format = GL_RGB;
                internalFormat = GL_RGB8;
                m_format = TextureFormat::Rgb;
            }
            else if (channels == 4)
            {
                format = GL_RGBA;
                internalFormat = GL_RGBA8;
                m_format = TextureFormat::Rgba;
            }

            m_width = width;
            m_height = height;

            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data));
            GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

            stbi_image_free(data);
        }
        else
        {
            SS_LOG_ERROR(fmt::format("Failed to load texture: {}", path));
        }
    }

    void OpenGLTexture::resize(uint32_t width, uint32_t height)
    {
        m_width = width;
        m_height = height;

        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void OpenGLTexture::setData(void *data, uint32_t size)
    {
        GLenum format = 0;
        GLenum internalFormat = 0;
        int bytesPerPixel = 0;
        if (m_format == TextureFormat::Red)
        {
            format = GL_RED;
            internalFormat = GL_RED;
            bytesPerPixel = 1;
        }
        else if (m_format == TextureFormat::Rgb)
        {
            format = GL_RGB;
            internalFormat = GL_RGB8;
            bytesPerPixel = 3;
        }
        else if (m_format == TextureFormat::Rgba)
        {
            format = GL_RGBA;
            internalFormat = GL_RGBA8;
            bytesPerPixel = 4;
        }
        else
        {
            SS_ASSERT(false, "Unknown texture format");
        }

        SS_ASSERT(size == m_width * m_height * bytesPerPixel, "Data must be entire texture");

        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data));
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void OpenGLTexture::setFormat(TextureFormat format)
    {
        m_format = format;
    }

    std::shared_ptr<Texture> Texture::create()
    {
        return std::make_shared<OpenGLTexture>();
    }
}