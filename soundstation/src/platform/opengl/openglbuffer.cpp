#include "pch.h"
#include "openglbuffer.h"

#include "platform/opengl/openglerror.h"

namespace SoundStation
{
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

    void OpenGLBuffer::setLayout(const BufferLayout &layout)
    {
        m_layout = layout;
        enableLayout();
    }

    uint32_t bufferDataTypeSize(BufferDataType type)
    {
        switch (type)
        {
        case BufferDataType::Float:
            return 1;
        case BufferDataType::Float2:
            return 2;
        case BufferDataType::Float3:
            return 3;
        case BufferDataType::Float4:
            return 4;
        case BufferDataType::Mat3:
            return 3 * 3;
        case BufferDataType::Mat4:
            return 4 * 4;
        case BufferDataType::Int:
            return 1;
        case BufferDataType::Int2:
            return 2;
        default:
            SS_ASSERT(false, "Unknown buffer data type");
            return 0;
        }
    }

    uint32_t bufferDataTypeToGlType(BufferDataType type)
    {
        switch (type)
        {
        case BufferDataType::Float:
            return GL_FLOAT;
        case BufferDataType::Float2:
            return GL_FLOAT;
        case BufferDataType::Float3:
            return GL_FLOAT;
        case BufferDataType::Float4:
            return GL_FLOAT;
        default:
            SS_ASSERT(false, "Unknown buffer data type");
        }
    }

    void OpenGLBuffer::enableLayout()
    {
        uint32_t stride = 0;
        uint32_t offset = 0;
        for (auto &element : m_layout.elements)
        {
            element.offset = offset;
            offset += bufferDataTypeSize(element.type);
            stride += bufferDataTypeSize(element.type);
        }

        GL_CALL(glBindBuffer(m_bufferTarget, m_rendererID));

        uint32_t i = 0;
        for (auto &element : m_layout.elements)
        {
            GL_CALL(glEnableVertexAttribArray(i));
            GL_CALL(glVertexAttribPointer(i, bufferDataTypeSize(element.type), bufferDataTypeToGlType(element.type), element.normalized ? GL_TRUE : GL_FALSE, stride, reinterpret_cast<const void *>(element.offset)));

            i++;
        }
    }

    void OpenGLBuffer::disableLayout()
    {
        uint32_t i = 0;
        for (auto &element : m_layout.elements)
        {
            GL_CALL(glDisableVertexAttribArray(i));
            i++;
        }
    }

    std::shared_ptr<Buffer> Buffer::create(BufferType type)
    {
        return std::make_shared<OpenGLBuffer>(type);
    }
}