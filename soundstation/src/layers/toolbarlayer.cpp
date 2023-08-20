#include "toolbarlayer.h"

#include <imgui.h>

namespace SoundStation
{
    ToolbarLayer::ToolbarLayer()
        : Layer("ToolbarLayer"),
          m_playImage("assets/images/play.png"),
          m_pauseImage("assets/images/pause.png")
    {
    }

    void ToolbarLayer::onAttach()
    {
    }

    void ToolbarLayer::onDetach()
    {
    }

    void ToolbarLayer::onUpdate(Timestep step)
    {
    }

    void ToolbarLayer::onUIRender()
    {
        ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        float buttonWidth = 30.0f;
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) / 2);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        if (ImGui::ImageButton(reinterpret_cast<void *>(m_playing ? m_pauseImage.texture()->rendererId() : m_playImage.texture()->rendererId()), {buttonWidth, buttonWidth}))
        {
            m_playing = !m_playing;
        }
        ImGui::PopStyleColor();
        ImGui::End();
    }
}