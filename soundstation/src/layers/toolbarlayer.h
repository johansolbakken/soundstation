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

        uint32_t cursor() const { return m_cursor; }
        void setCursor(uint32_t cursor) { m_cursor = cursor; }
        void incrementCursor() { ++m_cursor; }

        bool isPlaying() const { return m_playing; }

    private:
        Image m_playImage;
        Image m_pauseImage;
        bool m_playing = false;
        uint32_t m_cursor = 0;
    };
}
