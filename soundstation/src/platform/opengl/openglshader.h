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
        void setVec3(const std::string &name, const glm::vec3 &value) override;
        void setMat4(const std::string& name, const glm::mat4& value) override;

    private:
        uint32_t m_rendererID;
    };
}