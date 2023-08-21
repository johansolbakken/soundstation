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

        void onUIRender() override;

        static std::string staticName() { return "ToolbarLayer"; }

    private:
        Image m_playImage;
        Image m_pauseImage;
        bool m_playing = false;
    };
}
