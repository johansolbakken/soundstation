#include "playerlayer.h"

#include <imgui.h>

#include <filesystem>

#include "core/assert.h"

#include "renderer/renderer.h"

namespace SoundStation
{
    PlayerLayer::PlayerLayer()
        : Layer("PlayerLayer"),
          m_playImage("assets/images/play.png"),
          m_pauseImage("assets/images/pause.png")
    {
        m_noteImage = std::make_shared<Image>("assets/images/note.jpeg");
        m_shader = Shader::create("assets/shaders/texture.vert", "assets/shaders/texture.frag");
        m_framebuffer = Framebuffer::create(200, 200);
        m_framebuffer->unbind();
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
        m_framebuffer->bind();
        RenderCommand::setClearColor({0.0f, 0.0f, 0.0f, 1.0f});
        RenderCommand::clear();

        m_shader->bind();

        m_noteImage->texture()->bind();

        m_shader->setInt("tex", 0);

        RenderCommand::drawArrays(6);

        m_framebuffer->unbind();

        ImGui::Begin("Player");

        ImGui::Text("Sanity!");

        uint32_t viewportWidth = ImGui::GetContentRegionAvail().x;

        // m_framebuffer->bind();
        ImGui::Image(reinterpret_cast<void *>(m_noteImage->texture()->rendererId()), {200, 200}, {0, 1}, {1, 0});
        // m_framebuffer->unbind();

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