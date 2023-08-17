#include "playerlayer.h"

#include <imgui.h>

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

        // ImGui::Text("Sanity!");

        uint32_t viewportWidth = ImGui::GetContentRegionAvail().x;

        m_noteImage.resize(viewportWidth, viewportWidth);

        ImGui::Image(reinterpret_cast<void *>(m_noteImage.texture()->rendererId()), {float(m_noteImage.width()), float(m_noteImage.height())}, {0, 1}, {1, 0});

        ImGui::PushItemWidth(-1);

        if (ImGui::SliderFloat("##Current", &m_cursor, 0.0f, 100.0f))
        {
        }

        ImGui::PopItemWidth();

        float buttonWidth = 30.0f;
        m_playImage.resize(buttonWidth, buttonWidth);
        m_pauseImage.resize(buttonWidth, buttonWidth);

        float buttonXPos = (viewportWidth - buttonWidth) / 2.0f;
        ImGui::SetCursorPosX(buttonXPos);

        if (ImGui::ImageButton(reinterpret_cast<void *>(m_playing ? m_pauseImage.texture()->rendererId() : m_playImage.texture()->rendererId()), {buttonWidth, buttonWidth}))
        {
            m_playing = !m_playing;
        }

        ImGui::End();
    }
}