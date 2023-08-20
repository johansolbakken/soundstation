#pragma once

#include <memory>

namespace SoundStation
{
    enum class BufferType : uint8_t
    {
        Vertex,
        Index,
    };

    class Buffer 
    {
    public:
        virtual ~Buffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void setData(void *data, uint32_t size) = 0;

        virtual uint32_t rendererId() const = 0;

        static std::shared_ptr<Buffer> create(BufferType type);
    };
}