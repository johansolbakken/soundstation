#pragma once

#include <memory>
#include <string>

namespace SoundStation
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void setInt(const std::string &name, int value) = 0;

        static std::shared_ptr<Shader> create(const std::string &vertexSrc, const std::string &fragmentSrc);
    };
}