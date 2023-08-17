#pragma once

#include <memory>

namespace SoundStation {
    class Framebuffer {
    public:
        virtual ~Framebuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t colorAttachmentRendererID() const = 0;

        virtual uint32_t width() const = 0;
        virtual uint32_t height() const = 0;

        static std::shared_ptr<Framebuffer> create(uint32_t width, uint32_t height);
    };
}