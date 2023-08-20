#include "playerlayer.h"

#include <imgui.h>

#include "core/assert.h"
#include "core/application.h"

#include "audio/audiofilewriter.h"

#include <sstream>

namespace SoundStation
{
    PlayerLayer::PlayerLayer()
        : Layer("PlayerLayer"),
          m_noteImage("assets/images/note.jpeg"),
          m_playImage("assets/images/play.png"),
          m_pauseImage("assets/images/pause.png")
    {
    }

    std::string minSecString(float seconds)
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
        }
        else
        {
            ImGui::Text("No file selected");
        }

        ImGui::PushItemWidth(-1);
        float cursor = 0.0;
        float duration = 0.0;
        auto audioDevice = Application::instance().currentAudioDevice();
        if (audioDevice && m_audioFile != nullptr)
            cursor = audioDevice->currentFrame() / m_audioFile->sampleRate();
        if (m_audioFile != nullptr)
            duration = m_audioFile->duration();

        int cursorMinutes = int(cursor / 60.0f);
        int cursorSeconds = int(cursor - cursorMinutes * 60.0f);
        int durationMinutes = int(duration / 60.0f);
        int durationSeconds = int(duration - durationMinutes * 60.0f);
        std::string timeString = minSecString(cursor) + " / " + minSecString(duration);

        float newCursor = cursor;
        if (ImGui::SliderFloat("##Current", &newCursor, 0, duration, timeString.c_str()))
        {
            m_seeking = true;
            m_seekPosition = newCursor;
        }
        else if (m_seeking)
        {
            if (audioDevice)
            {
                audioDevice->seek(m_seekPosition * m_audioFile->sampleRate());
            }
            m_seeking = false;
        }
        ImGui::PopItemWidth();

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