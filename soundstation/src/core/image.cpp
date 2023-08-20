#include "image.h"

#include "core/assert.h"

namespace SoundStation
{
    Image::Image(const std::filesystem::path &path)
        : m_path(path)
    {
        // SS_LOG_INFO(fmt::format("Loading image: {}", path.string()));
        SS_ASSERT(std::filesystem::exists(path), "Image does not exist!");

        m_texture = Texture::create();
        m_texture->load(std::filesystem::absolute(path).string());
        m_width = m_texture->width();
        m_height = m_texture->height();
        m_texture->bind();
    }

    Image::~Image()
    {
    }

    void Image::resize(uint32_t width, uint32_t height)
    {
        if (width == m_width && height == m_height)
        {
            return;
        }

        m_width = width;
        m_height = height;
    }
}
