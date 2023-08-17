#include "opengltexture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "core/assert.h"

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
        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));
        GL_CALL(glActiveTexture(GL_TEXTURE0));
    }

    void OpenGLTexture::unbind()
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
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

            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));
            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
            GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

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