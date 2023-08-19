#pragma once

#include "core/layer.h"
#include "core/image.h"

namespace SoundStation
{
    class ToolbarLayer : public Layer
    {
    public:
        ToolbarLayer();
        ~ToolbarLayer() override = default;

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep step) override;
        void onUIRender() override;

    private:
        Image m_playImage;
        Image m_pauseImage;
        bool m_playing = false;
    };
}

