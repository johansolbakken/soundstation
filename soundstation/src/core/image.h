#pragma once

#include "renderer/texture.h"

namespace SoundStation
{
    class Image
    {
    public:
        Image(const std::filesystem::path &path);
        ~Image();

        void resize(uint32_t width, uint32_t height);

        uint32_t width() const { return m_width; }
        uint32_t height() const { return m_height; }

        auto texture() const { return m_texture; }

    private:
        std::filesystem::path m_path;
        uint32_t m_width = 0;
        uint32_t m_height = 0;

        std::shared_ptr<Texture> m_texture = nullptr;
    };
}