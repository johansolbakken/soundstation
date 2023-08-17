#pragma once

#include <string>
#include <memory>

namespace SoundStation
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void load(const std::string &path) = 0;

        virtual uint32_t rendererId() const = 0;

        virtual uint32_t width() const = 0;
        virtual uint32_t height() const = 0;

        static std::shared_ptr<Texture> create();
    };
}