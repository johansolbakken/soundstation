#pragma once

namespace SoundStation
{
    enum class BufferType : uint8_t
    {
        Vertex,
        Index,
    };

    enum class BufferDataType : uint8_t
    {
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool,
    };

    struct BufferElement
    {
        BufferDataType type;
        std::string name = "";
        uint32_t offset = 0;
        bool normalized = false;
    };

    struct BufferLayout
    {
        std::vector<BufferElement> elements;
    };

    class Buffer
    {
    public:
        virtual ~Buffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void setData(void *data, uint32_t size) = 0;

        virtual const BufferLayout &layout() const = 0;
        virtual void setLayout(const BufferLayout &layout) = 0;
        virtual void enableLayout() = 0;
        virtual void disableLayout() = 0;

        virtual uint32_t rendererId() const = 0;

        static std::shared_ptr<Buffer> create(BufferType type);
    };
}