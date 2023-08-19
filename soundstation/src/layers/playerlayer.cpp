#include "playerlayer.h"

#include <imgui.h>

#include "core/assert.h"

namespace SoundStation
{
    PlayerLayer::PlayerLayer()
        : Layer("PlayerLayer"),
          m_noteImage("assets/images/note.jpeg"),
          m_playImage("assets/images/play.png"),
          m_pauseImage("assets/images/pause.png"),
          m_audio(Audio::create("assets/sound/Lizza Bizzaz.aif"))
    {
        float duration = 5.0f; // seconds
        float sampleRate = 41000.0f;
        float frequency = 440.0f;
        float amplitude = 0.5f;
        size_t numSamples = static_cast<size_t>(duration * sampleRate);
        float *data = new float[numSamples * 2];
        for (size_t i = 0; i < numSamples; i++)
        {
            float t = static_cast<float>(i) / sampleRate;
            data[i * 2] = amplitude * sin(2.0f * M_PI * frequency * t);
            data[i * 2 + 1] = amplitude * sin(2.0f * M_PI * frequency * t);
        }

        m_audioBuffer = std::make_shared<AudioBuffer>(data, numSamples * 2, sampleRate, AudioBufferFormat::Float32Bit, 2);

        m_audioDevice = AudioDevice::create();
        m_audioDevice->setAudioBuffer(m_audioBuffer);
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
            }
            else
            {
                // m_audio->pause();
            }
        }

        ImGui::End();
    }
}