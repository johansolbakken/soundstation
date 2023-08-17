#pragma once

#include "core/layer.h"

namespace SoundStation
{
    class PlayerLayer : public Layer
    {
    public:
        PlayerLayer();
        ~PlayerLayer() override;

        void onAttach() override;
        void onDetach() override;
        void onUpdate() override;
        void onUIRender() override;

    private:
        bool m_playing = true;
        float m_cursor = 0.0;
    };
}