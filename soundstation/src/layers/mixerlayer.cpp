#include "pch.h"
#include "mixerlayer.h"

#include <imgui.h>

#include "core/application.h"

#include "layers/toolbarlayer.h"

namespace SoundStation
{
    MixerLayer::MixerLayer()
        : Layer(staticName())
    {
    }

    void MixerLayer::onAttach()
    {
        m_audioFile = AudioFile::create("assets/sound/Lizza Bizzaz.aif");
        m_fader = Fader::create(1.0f);

        float sampleRate = Application::instance().currentProject().sampleRate();
        auto audioDevice = Application::instance().currentAudioDevice();
        size_t size = audioDevice->bufferSize();
        uint32_t channels = 2;
        AudioBufferFormat format = AudioBufferFormat::Float32Bit;
        float *data = new float[size * channels];
        for (int i = 0; i < size * channels; ++i)
            data[i] = 0.0f;
        m_outputBuffer = AudioBuffer::create(data, size, sampleRate, format, channels);

        auto newBuffer = m_audioFile->audioBuffer()->convertSampleRate(sampleRate);
        m_audioFile->setAudioBuffer(newBuffer);

        Application::instance().currentAudioDevice()->setAudioCallback(std::bind(&MixerLayer::audioCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    void MixerLayer::onDetach()
    {
    }

    void MixerLayer::onUpdate(Timestep t)
    {
    }

    // -inf to 10 dB
    float levelToDB(float level)
    {
        return 20.0f * std::log10(std::clamp(level, 0.0001f, 1.0f));
    }

    void MixerLayer::renderFader(const std::string &name, std::shared_ptr<Fader> fader)
    {
        ImGui::BeginGroup();

        float level = m_fader->level();
        std::stringstream ss;
        if (level == 0.0f)
        {
            ss << "-inf dB";
        }
        else
        {
            ss << std::fixed << std::setprecision(1);
            ss << levelToDB(level) << " dB";
        }
        std::string levelString = ss.str();
        if (ImGui::VSliderFloat("Level", {50, 300}, &level, 0.0f, 1.0f, levelString.c_str()))
            m_fader->setLevel(level);
        ImGui::Text("Main Out");

        ImGui::EndGroup();
    }

    void MixerLayer::onUIRender()
    {
        ImGui::Begin("Mixer");

        // renderFader("Main Out", m_fader);
        // ImGui::SameLine();
        renderFader("Main Out", m_fader);

        ImGui::End();
    }

    void MixerLayer::audioCallback(float *left, float *right, uint32_t frames)
    {
        auto outputData = reinterpret_cast<float(*)[2]>(m_outputBuffer->data());
        for (int i = 0; i < frames; ++i)
        {
            outputData[i][0] = 0.0f;
            outputData[i][1] = 0.0f;
        }

        // Input -> mixer
        auto toolbarLayer = Application::getLayer<ToolbarLayer>();
        if (m_audioFile && toolbarLayer && toolbarLayer->isPlaying())
        {
            auto inputData = reinterpret_cast<float(*)[2]>(m_audioFile->audioBuffer()->data());
            auto outputData = reinterpret_cast<float(*)[2]>(m_outputBuffer->data());
            for (int i = 0; i < frames; ++i)
            {
                if (toolbarLayer->cursor() >= m_audioFile->audioBuffer()->frames())
                {
                    outputData[i][0] = 0.0f;
                    outputData[i][1] = 0.0f;
                    continue;
                }

                outputData[i][0] = inputData[toolbarLayer->cursor()][0];
                outputData[i][1] = inputData[toolbarLayer->cursor()][1];
                toolbarLayer->incrementCursor();
            }
        }

        m_fader->process(m_outputBuffer->data(), int(m_outputBuffer->size()));

        // Output -> device
        auto audioDevice = Application::instance().currentAudioDevice();
        auto adSampleRate = audioDevice->sampleRate();
        auto bufferSampleRate = m_outputBuffer->sampleRate();
        /*for (int i = 0; i < frames; ++i)
        {
            const float *sample = outputData[i];
            left[i] = sample[0];
            right[i] = sample[1];
        }*/
        for (int i = 0; i < frames; ++i)
        {
            float convertedFrame = (float)i * (bufferSampleRate / adSampleRate);
            const float *sample = outputData[int(convertedFrame)];
            left[i] = sample[0];
            right[i] = sample[1];
        }
    }
}
