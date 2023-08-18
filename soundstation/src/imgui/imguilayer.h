#pragma once

#include "core/layer.h"

namespace SoundStation {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep step) override;

        void begin();
        void end();
    };
}