#pragma once

#include "renderer/shader.h"

namespace SoundStation
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~OpenGLShader() override;

        void bind() override;
        void unbind() override;

        void setInt(const std::string &name, int value) override;

    private:
        uint32_t m_rendererID;
    };
}