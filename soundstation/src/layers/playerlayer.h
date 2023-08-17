#pragma once

#include "core/layer.h"

#include "core/image.h"

#include "renderer/shader.h"
#include "renderer/framebuffer.h"

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

        std::shared_ptr<Image> m_noteImage;
        Image m_playImage;
        Image m_pauseImage;

        std::shared_ptr<Shader> m_shader = nullptr;
        std::shared_ptr<Framebuffer> m_framebuffer = nullptr;
    };
}