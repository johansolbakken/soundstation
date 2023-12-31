#include "pch.h"
#include "openglshader.h"

#include <glad/glad.h>

#include "platform/opengl/openglerror.h"

#include <glm/gtc/type_ptr.hpp>

namespace SoundStation
{
    OpenGLShader::OpenGLShader(const std::string &vertexFile, const std::string &fragmentFile)
    {
        std::string vertexSrc;
        std::string fragmentSrc;

        std::ifstream vertexFileIn(vertexFile);
        std::ifstream fragmentFileIn(fragmentFile);

        if (!vertexFileIn.is_open())
        {
            throw std::runtime_error("Vertex shader file does not exist");
        }

        if (!fragmentFileIn.is_open())
        {
            throw std::runtime_error("Fragment shader file does not exist");
        }

        std::string line;
        while (std::getline(vertexFileIn, line))
        {
            vertexSrc += line + "\n";
        }

        while (std::getline(fragmentFileIn, line))
        {
            fragmentSrc += line + "\n";
        }

        GL_CALL(m_rendererID = glCreateProgram());

        uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char *vertexSrcCStr = vertexSrc.c_str();
        GL_CALL(glShaderSource(vertexShader, 1, &vertexSrcCStr, nullptr));
        GL_CALL(glCompileShader(vertexShader));

        int success;
        char infoLog[512];
        GL_CALL(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            GL_CALL(glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog));
            SS_LOG_ERROR(fmt::format("Vertex shader compilation failed: {}", infoLog));
        }

        uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *fragmentSrcCStr = fragmentSrc.c_str();
        GL_CALL(glShaderSource(fragmentShader, 1, &fragmentSrcCStr, nullptr));
        GL_CALL(glCompileShader(fragmentShader));

        GL_CALL(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            GL_CALL(glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog));
            SS_LOG_ERROR(fmt::format("Fragment shader compilation failed: {}", infoLog));
        }

        GL_CALL(glAttachShader(m_rendererID, vertexShader));
        GL_CALL(glAttachShader(m_rendererID, fragmentShader));
        GL_CALL(glLinkProgram(m_rendererID));

        GL_CALL(glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success));
        if (!success)
        {
            GL_CALL(glGetProgramInfoLog(m_rendererID, 512, nullptr, infoLog));
            SS_LOG_ERROR(fmt::format("Shader program linking failed: {}", infoLog));
        }

        GL_CALL(glDeleteShader(vertexShader));
        GL_CALL(glDeleteShader(fragmentShader));
    }

    OpenGLShader::~OpenGLShader()
    {
        GL_CALL(glDeleteProgram(m_rendererID));
    }

    void OpenGLShader::bind()
    {
        GL_CALL(glUseProgram(m_rendererID));
    }

    void OpenGLShader::unbind()
    {
        GL_CALL(glUseProgram(0));
    }

    void OpenGLShader::setInt(const std::string &name, int value)
    {
        auto location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
        {
            SS_LOG_WARN(fmt::format("Uniform {} does not exist", name));
            return;
        }
        GL_CALL(glUniform1i(location, value));
    }

    void OpenGLShader::setVec3(const std::string &name, const glm::vec3 &value)
    {
        auto location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
        {
            SS_LOG_WARN(fmt::format("Uniform {} does not exist", name));
            return;
        }
        GL_CALL(glUniform3fv(location, 1, glm::value_ptr(value)));
    }

    void OpenGLShader::setMat4(const std::string &name, const glm::mat4 &value)
    {
        auto location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
        {
            SS_LOG_WARN(fmt::format("Uniform {} does not exist", name));
            return;
        }
        GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
    }

    std::shared_ptr<Shader> Shader::create(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
    }
}