#include "playerlayer.h"

#include <imgui.h>

#include <filesystem>

#include "core/assert.h"

namespace SoundStation
{
    PlayerLayer::PlayerLayer()
        : Layer("PlayerLayer")
    {
        std::string path = "assets/images/note.jpeg";
        std::filesystem::path p = path;
        SS_ASSERT(std::filesystem::exists(p), "File does not exist!");

        m_texture = Texture::create();
        m_texture->load(path);
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

        ImGui::Image(reinterpret_cast<void *>(m_texture->rendererId()), {float(viewportWidth), float(viewportWidth)}, {0, 1}, {1, 0});

        ImGui::PushItemWidth(-1);

        if (ImGui::SliderFloat("##Current", &m_cursor, 0.0f, 100.0f))
        {
        }

        ImGui::PopItemWidth();

        // center button in middle

        float buttonWidth = 100.0f;
        float buttonXPos = (viewportWidth - buttonWidth) / 2.0f;
        ImGui::SetCursorPosX(buttonXPos);
        if (ImGui::Button(m_playing ? "Pause" : "Play", {buttonWidth, 0}))
        {
            m_playing = !m_playing;
        }

        ImGui::End();
    }
}