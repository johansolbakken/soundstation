#include "image.h"

namespace SoundStation
{
    Image::Image(const std::filesystem::path &path)
        : m_path(path)
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Image file does not exist");
        }

        m_texture = Texture::create();
        m_texture->load(std::filesystem::absolute(path).string());
        m_width = m_texture->width();
        m_height = m_texture->height();
    }

    Image::~Image()
    {
    }
}
