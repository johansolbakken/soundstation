#pragma once

#include <string>
#include <memory>

namespace SoundStation
{
    enum class TextureFormat
    {
        None = 0,
        Rgb = 1,
        Rgba = 2,
        Red = 3,
    };

    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void load(const std::string &path) = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;
        virtual void setData(void *data, uint32_t size) = 0;
        virtual void setFormat(TextureFormat format) = 0;

        virtual uint32_t rendererId() const = 0;

        virtual uint32_t width() const = 0;
        virtual uint32_t height() const = 0;
        virtual TextureFormat format() const = 0;

        static std::shared_ptr<Texture> create();
    };
}