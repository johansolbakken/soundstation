#pragma once

#include <string>

#include "core/time.h"

namespace SoundStation
{
    class Layer
    {
    public:
        Layer(const std::string& name);
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Timestep delta) {}
        virtual void onUIRender() {}

    private:
        std::string m_name;
    };
}