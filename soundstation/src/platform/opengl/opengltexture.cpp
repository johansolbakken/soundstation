#include "opengltexture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "core/assert.h"

namespace SoundStation
{
    OpenGLTexture::OpenGLTexture()
    {
        glGenTextures(1, &m_rendererID);

        glBindTexture(GL_TEXTURE_2D, m_rendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_rendererID);
    }

    void OpenGLTexture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_rendererID);
        glActiveTexture(GL_TEXTURE0);
    }

    void OpenGLTexture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture::load(const std::string &path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 1);

        if (data)
        {
            SS_LOG_DEBUG(fmt::format("Loaded texture: {}x{}x{}", width, height, channels));
            GLenum format = 0;
            if (channels == 1)
                format = GL_RED;
            else if (channels == 3)
                format = GL_RGB;
            else if (channels == 4)
                format = GL_RGBA;

            m_width = width;
            m_height = height;

            glBindTexture(GL_TEXTURE_2D, m_rendererID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
        }
        else
        {
            SS_ASSERT(false, "Failed to load texture");
        }
    }

    std::shared_ptr<Texture> Texture::create()
    {
        return std::make_shared<OpenGLTexture>();
    }
}