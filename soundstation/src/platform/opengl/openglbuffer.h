#pragma once

#include "renderer/buffer.h"

namespace SoundStation
{
    class OpenGLBuffer : public Buffer
    {
    public:
        OpenGLBuffer(BufferType type);
        ~OpenGLBuffer() override;

        void bind() override;
        void unbind() override;

        void setData(void *data, uint32_t size) override;

        uint32_t rendererId() const override { return m_rendererID; }

    private:
        uint32_t m_rendererID = 0;
        uint32_t m_bufferTarget = 0;
        BufferType m_type;
    };
}