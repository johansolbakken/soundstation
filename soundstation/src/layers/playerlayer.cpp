#include "playerlayer.h"

#include <imgui.h>

namespace SoundStation
{
    PlayerLayer::PlayerLayer()
        : Layer("PlayerLayer")
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
        ImGui::Text("Image");

        if (ImGui::Button(m_playing ? "Pause" : "Play"))
        {
            m_playing = !m_playing;
        }

        if (ImGui::SliderFloat("##Current", &m_cursor, 0.0f, 100.0f))
        {
        }

        ImGui::End();
    }
}