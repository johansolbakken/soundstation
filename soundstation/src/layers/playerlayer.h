#pragma once

#include "core/layer.h"

#include "renderer/texture.h"

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
        bool m_playing = false;
        float m_cursor = 0.0;

        std::shared_ptr<Texture> m_texture = nullptr;
    };
}