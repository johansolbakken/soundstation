#pragma once

#include <string>

namespace SoundStation
{
    class Layer
    {
    public:
        Layer(const std::string& name);
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onUIRender() {}

    private:
        std::string m_name;
    };
}