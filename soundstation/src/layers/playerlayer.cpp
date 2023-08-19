#include "playerlayer.h"

#include <imgui.h>

#include "core/assert.h"

#include "audio/audiofilewriter.h"

namespace SoundStation
{
    PlayerLayer::PlayerLayer()
        : Layer("PlayerLayer"),
          m_noteImage("assets/images/note.jpeg"),
          m_playImage("assets/images/play.png"),
          m_pauseImage("assets/images/pause.png"),
          m_audio(Audio::create("assets/sound/Lizza Bizzaz.aif"))
    {
        m_audioBuffer = AudioFileWriter::read("assets/sound/Lizza Bizzaz.aif");

        m_audioDevice = AudioDevice::create();
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
        m_audio->update();
        m_audioDevice->update(step);
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

        float cursor = m_audio->position();
        if (ImGui::SliderFloat("##Current", &cursor, 0.0f, m_audio->duration()))
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
            if (m_playing)
            {
                // m_audio->play();
                m_audioDevice->setAudioBuffer(m_audioBuffer);
            }
            else
            {
                // m_audio->pause();
                m_audioDevice->setAudioBuffer(nullptr);
            }
        }

        if (ImGui::Button("Write buffer to file")) {
            AudioFileWriter::write("test.aif", m_audioBuffer, AudioFileFormat::Aiff);
        }

        ImGui::End();
    }
}