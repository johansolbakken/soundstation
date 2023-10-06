#include "pch.h"
#include "mixerlayer.h"

#include <imgui.h>

#include "core/application.h"

#include "layers/toolbarlayer.h"

#include <glm/glm.hpp>

namespace SoundStation
{
    MixerLayer::MixerLayer()
        : Layer(staticName())
    {
    }

    void MixerLayer::onAttach()
    {
        m_fader = Fader::create(1.0f);

        auto project = Application::instance().currentProject();
        uint32_t sampleRate = project.sampleRate();
        size_t size = project.bufferSize();
        uint32_t channels = 2;
        AudioBufferFormat format = AudioBufferFormat::Float32Bit;
        float *data = new float[size * channels];
        for (int i = 0; i < size * channels; ++i)
            data[i] = 0.0f;
        m_outputBuffer = AudioBuffer::create(data, size, sampleRate, format, channels);

        // TODO: import audio in project sample rate
        m_audioFile = AudioFile::create("assets/sound/Lizza Bizzaz.aif");

        Application::instance().currentAudioDevice()->setAudioCallback(std::bind(&MixerLayer::audioCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
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
        return 20.0f * std::log10(glm::clamp(level, 0.0001f, 1.0f));
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

    void MixerLayer::audioCallback(float *data, uint32_t frames, uint32_t channels, float sampleRate)
    {
        SS_ASSERT(channels == 2, "Only stereo supported");
        SS_ASSERT(m_outputBuffer->channels() == 2, "Only stereo supported");

        // bufferSize = frames * channels

        // Clear output buffer
        {
            for (int i = 0; i < m_outputBuffer->size(); i++)
                m_outputBuffer->data()[i] = 0.0f;
        }

        // Adding audio file to output buffer
        {
            auto toolbarLayer = Application::getLayer<ToolbarLayer>();
            if (m_audioFile && toolbarLayer && toolbarLayer->isPlaying())
            {
                SS_ASSERT(m_audioFile->audioBuffer()->channels() == 2, "Only stereo supported");

                auto bufferData = m_outputBuffer->data();
                auto bufferFrames = m_outputBuffer->frames();
                auto bufferChannels = m_outputBuffer->channels();
                auto bufferSampleRate = m_outputBuffer->sampleRate();

                auto audioData = m_audioFile->audioBuffer()->data();
                auto audioFrames = m_audioFile->audioBuffer()->frames();
                auto audioChannels = m_audioFile->audioBuffer()->channels();
                auto audioSampleRate = m_audioFile->audioBuffer()->sampleRate();

                auto sampleRatio = static_cast<float>(audioSampleRate) / static_cast<float>(bufferSampleRate);

                for (int i = 0; i < bufferFrames; i++)
                {
                    // if (toolbarLayer->cursor() >= audioFrames)
                    //     break;
                    // bufferData[i] += audioData[toolbarLayer->cursor()];
                    // toolbarLayer->incrementCursor();
                }
            }
        }

        // Resample output buffer to data
        {
            SS_LOG_DEBUG(fmt::format("frames={}, m_outputBuffer->frames()={}", frames, m_outputBuffer->frames()));
            SS_ASSERT(frames == m_outputBuffer->frames(), "Frames must be equal");

            auto bufferData = m_outputBuffer->data();
            auto bufferFrames = m_outputBuffer->frames();
            auto bufferChannels = m_outputBuffer->channels();
            auto bufferSampleRate = m_outputBuffer->sampleRate();
            for (int i = 0; i < frames * channels; i++)
            {
                data[i] = bufferData[i];
            }
        }

        /*
        // Input -> mixer
        auto toolbarLayer = Application::getLayer<ToolbarLayer>();
        if (m_audioFile && toolbarLayer && toolbarLayer->isPlaying())
        {
            auto inputData = reinterpret_cast<float(*)[2]>(m_audioFile->audioBuffer()->data());
            for (int i = 0; i < outputDataFrames; ++i)
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
        auto deviceSampleRate = audioDevice->sampleRate();

        auto sizeRatio = static_cast<float>(m_outputBuffer->frames()) / static_cast<float>(frames);

        for (int i = 0; i < frames; ++i)
        {
            // Calculate the position in the output buffer
            float position = static_cast<float>(i) * sizeRatio;

            // Linear interpolation (you can use more advanced techniques)
            int floorPos = static_cast<int>(std::floor(position));
            int ceilPos = static_cast<int>(std::ceil(position));
            float fraction = position - floorPos;

            // Interpolate between two samples in the output buffer
            const float *sample1 = outputData[floorPos];
            const float *sample2 = outputData[ceilPos];

            left[i] = (1.0f - fraction) * sample1[0] + fraction * sample2[0];
            right[i] = (1.0f - fraction) * sample1[1] + fraction * sample2[1];
        }*/
    }
}
