#include "playerlayer.h"

#include <imgui.h>

#include "core/assert.h"
#include "core/application.h"

#include "audio/audiofilewriter.h"

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

    void PlayerLayer::onUpdate(Timestep step)
    {
        // m_audioDevice->update(step);
    }

    void PlayerLayer::onUIRender()
    {
        // begin with fixed size
        ImGui::SetNextWindowSize({300, 400});
        ImGui::Begin("Player", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        // ImGui::Text("Sanity!");

        uint32_t viewportWidth = ImGui::GetContentRegionAvail().x;

        m_noteImage.resize(viewportWidth, viewportWidth);

        ImGui::Image(reinterpret_cast<void *>(m_noteImage.texture()->rendererId()), {float(m_noteImage.width()), float(m_noteImage.height())}, {0, 1}, {1, 0});

        ImGui::PushItemWidth(-1);

        // float cursor = m_audio->position();
        /*if (ImGui::SliderFloat("##Current", &cursor, 0.0f, m_audio->duration()))
        {
        }*/

        ImGui::PopItemWidth();

        float buttonWidth = 30.0f;
        m_playImage.resize(buttonWidth, buttonWidth);
        m_pauseImage.resize(buttonWidth, buttonWidth);

        float buttonXPos = (viewportWidth - buttonWidth) / 2.0f;
        ImGui::SetCursorPosX(buttonXPos);

        if (ImGui::ImageButton(reinterpret_cast<void *>(m_playing ? m_pauseImage.texture()->rendererId() : m_playImage.texture()->rendererId()), {buttonWidth, buttonWidth}) && m_audioFile != nullptr)
        {
            if (Application::instance().currentAudioDevice() != nullptr)
            {
                m_playing = !m_playing;
                if (m_playing)
                {
                    Application::instance().currentAudioDevice()->setAudioBuffer(m_audioFile->audioBuffer());
                }
                else
                {
                    Application::instance().currentAudioDevice()->setAudioBuffer(nullptr);
                }
            }
        }

        static bool m_showLoadAudioFileModal = false;
        if (m_showLoadAudioFileModal)
        {
            ImGui::OpenPopup("Load Audio File");
            m_showLoadAudioFileModal = false;
        }
        if (ImGui::Button("Load Audio File"))
        {
            m_showLoadAudioFileModal = true;
        }

        if (ImGui::BeginPopupModal("Load Audio File", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            static char m_filePath[256] = {0};
            ImGui::InputText("File Path", m_filePath, 256);

            if (ImGui::Button("Load"))
            {
                SS_LOG_INFO(fmt::format("Loading audio file: {}", m_filePath));
                m_audioFile = std::make_shared<AudioFile>(m_filePath);
                m_playing = false;
                m_showLoadAudioFileModal = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("Cancel"))
            {
                m_showLoadAudioFileModal = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }
}