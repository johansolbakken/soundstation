#include "playerlayer.h"

#include <imgui.h>

#include <filesystem>

#include "core/assert.h"

namespace SoundStation
{
    PlayerLayer::PlayerLayer()
        : Layer("PlayerLayer"),
          m_noteImage("assets/images/note.jpeg"),
          m_playImage("assets/images/play.png"),
          m_pauseImage("assets/images/pause.png")
    {
    }

    PlayerLayer::~PlayerLayer()
    {
    }

    void PlayerLayer::onAttach()
    {
    }

    void PlayerLayer::onDetach()
    {
    }

    void PlayerLayer::onUpdate()
    {
        if (m_playing)
        {
            m_cursor += 0.1f;
        }
    }

    void PlayerLayer::onUIRender()
    {
        ImGui::Begin("Player");

        uint32_t viewportWidth = ImGui::GetContentRegionAvail().x;

        ImGui::Image(reinterpret_cast<void *>(m_noteImage.texture()->rendererId()), {float(viewportWidth), float(viewportWidth)}, {0, 1}, {1, 0});

        ImGui::PushItemWidth(-1);

        if (ImGui::SliderFloat("##Current", &m_cursor, 0.0f, 100.0f))
        {
        }

        ImGui::PopItemWidth();

        // center button in middle

        float buttonWidth = 100.0f;
        float buttonXPos = (viewportWidth - buttonWidth) / 2.0f;
        ImGui::SetCursorPosX(buttonXPos);
        /*if (ImGui::Button(m_playing ? "Pause" : "Play", {buttonWidth, 0}))
        {
            m_playing = !m_playing;
        }*/
        if (ImGui::ImageButton(reinterpret_cast<void *>(m_playing ? m_pauseImage.texture()->rendererId() : m_playImage.texture()->rendererId()), {buttonWidth, buttonWidth}))
        {
            m_playing = !m_playing;
        }

        ImGui::End();
    }
}