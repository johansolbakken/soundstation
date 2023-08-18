#pragma once

#include "audio/audiodevice.h"

namespace SoundStation
{
    class MacOSAudioDevice : public AudioDevice
    {
    public:
        MacOSAudioDevice();
        ~MacOSAudioDevice() override;
        void setAudioBuffer(const std::shared_ptr<AudioBuffer> &audioBuffer) override;
        void update() override;

        const std::string &name() const override { return m_name; }
        float sampleRate() const override { return m_sampleRate; }
        size_t channels() const override { return m_channels; }
        float bufferSize() const override { return m_bufferSize; }

    private:
        std::shared_ptr<AudioBuffer> m_audioBuffer = nullptr;

        std::string m_name = "Uninitialized";
        float m_sampleRate = 0;
        size_t m_channels = 0;
        float m_bufferSize = 0;
    };
}
