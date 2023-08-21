#pragma once

#include "core/layer.h"

namespace SoundStation
{
    class MenuBarLayer : public Layer
    {
    public:
        MenuBarLayer();
        ~MenuBarLayer() override = default;

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep t) override;
        void onUIRender() override;

        static std::string staticName() { return "MenuBarLayer"; }
    };
}