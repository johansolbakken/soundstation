#include "openglbuffer.h"

#include "core/assert.h"

#include "platform/opengl/openglerror.h"

namespace SoundStation {
    OpenGLBuffer::OpenGLBuffer(BufferType type)
        : m_type(type)
    {
        m_bufferTarget = 0;
        switch (m_type)
        {
        case BufferType::Vertex:
            m_bufferTarget = GL_ARRAY_BUFFER;
            break;
        case BufferType::Index:
            m_bufferTarget = GL_ELEMENT_ARRAY_BUFFER;
            break;
        default:
            SS_ASSERT(false, "Unknown buffer type");
            break;
        }

        GL_CALL(glGenBuffers(1, &m_rendererID));
    }

    OpenGLBuffer::~OpenGLBuffer()
    {
        GL_CALL(glDeleteBuffers(1, &m_rendererID));
    }

    void OpenGLBuffer::bind()
    {    
        GL_CALL(glBindBuffer(m_bufferTarget, m_rendererID));
    }

    void OpenGLBuffer::unbind()
    {
        GL_CALL(glBindBuffer(m_bufferTarget, 0));
    }

    void OpenGLBuffer::setData(void *data, uint32_t size)
    {
        GL_CALL(glBindBuffer(m_bufferTarget, m_rendererID));
        GL_CALL(glBufferData(m_bufferTarget, size, data, GL_STATIC_DRAW));
    }

    std::shared_ptr<Buffer> Buffer::create(BufferType type)
    {
        return std::make_shared<OpenGLBuffer>(type);
    }
}