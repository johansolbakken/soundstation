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

    void PlayerLayer::onUIRender()
    {
        ImGui::SetNextWindowSize({300, 450});
        ImGui::Begin("Player", nullptr, ImGuiWindowFlags_NoResize);

        uint32_t viewportWidth = ImGui::GetContentRegionAvail().x;

        m_noteImage.resize(viewportWidth, viewportWidth);

        ImGui::Image(reinterpret_cast<void *>(m_noteImage.texture()->rendererId()), {float(m_noteImage.width()), float(m_noteImage.height())}, {0, 1}, {1, 0});

        if (m_audioFile != nullptr)
        {
            ImGui::Text("File: %s", m_audioFile->filename().c_str());
            auto duration = m_audioFile->duration();
            auto minutes = int(duration / 60.0f);
            auto seconds = int(duration - minutes * 60.0f);
            ImGui::Text("Duration: %02d:%02d", minutes, seconds);
        }
        else
        {
            ImGui::Text("No file selected");
        }

        /*ImGui::PushItemWidth(-1);
        float cursor = m_audio->position();
        if (ImGui::SliderFloat("##Current", &cursor, 0.0f, m_audio->duration()))
        {
        }
        ImGui::PopItemWidth();*/

        float buttonWidth = 30.0f;
        m_playImage.resize(buttonWidth, buttonWidth);
        m_pauseImage.resize(buttonWidth, buttonWidth);

        float buttonXPos = (viewportWidth - buttonWidth) / 2.0f;
        ImGui::SetCursorPosX(buttonXPos);
        auto texture = m_playing ? m_pauseImage.texture()->rendererId() : m_playImage.texture()->rendererId();
        if (ImGui::ImageButton(reinterpret_cast<void *>(texture), {buttonWidth, buttonWidth}) && m_audioFile != nullptr)
        {
            if (Application::instance().currentAudioDevice() != nullptr)
            {
                if (!m_playing)
                    play();
                else
                    pause();
            }
        }

        ImGui::End();
    }

    void PlayerLayer::setAudioFile(const std::shared_ptr<AudioFile> &file)
    {
        if (m_playing)
            pause();
        m_audioFile = file;
    }

    void PlayerLayer::play()
    {
        auto audioDevice = Application::instance().currentAudioDevice();
        if (audioDevice)
        {
            audioDevice->setAudioBuffer(m_audioFile->audioBuffer());
        }
        m_playing = true;
    }

    void PlayerLayer::pause()
    {

        auto audioDevice = Application::instance().currentAudioDevice();
        if (audioDevice)
        {
            audioDevice->setAudioBuffer(nullptr);
        }
        m_playing = false;
    }
}