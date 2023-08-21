#include "pch.h"
#include "toolbarlayer.h"

#include <imgui.h>

#include "core/application.h"

#include "layers/projectlayer.h"

namespace SoundStation
{
    ToolbarLayer::ToolbarLayer()
        : Layer(staticName()),
          m_playImage("assets/images/play.png"),
          m_pauseImage("assets/images/pause.png")
    {
    }

    static std::string minSecString(float seconds)
    {
        int minutes = int(seconds / 60.0f);
        int secs = int(seconds - minutes * 60.0f);
        std::stringstream ss;
        if (minutes < 10)
            ss << "0";
        ss << minutes << ":";
        if (secs < 10)
            ss << "0";
        ss << secs;
        return ss.str();
    }

    void ToolbarLayer::onUIRender()
    {
        int sampleRate = 0;
        if (auto projectLayer = Application::getLayer<ProjectLayer>())
            sampleRate = projectLayer->project().sampleRate();

        ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        float buttonWidth = 30.0f;
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) / 2);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        if (ImGui::ImageButton(reinterpret_cast<void *>(m_playing ? m_pauseImage.texture()->rendererId() : m_playImage.texture()->rendererId()), {buttonWidth, buttonWidth}))
        {
            m_playing = !m_playing;
        }
        ImGui::PopStyleColor();
        ImGui::SameLine();
        auto cursor = minSecString(m_cursor / float(sampleRate));
        ImGui::Text("%s", cursor.c_str());
        ImGui::End();
    }
}