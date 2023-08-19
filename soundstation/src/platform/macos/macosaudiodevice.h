#pragma once

#include "audio/audiodevice.h"

#include <AudioToolbox/AudioToolbox.h>

namespace SoundStation
{
    class MacOSAudioDevice : public AudioDevice
    {
    public:
        MacOSAudioDevice(uint32_t deviceID);
        ~MacOSAudioDevice() override;
        void setAudioBuffer(const std::shared_ptr<AudioBuffer> &audioBuffer) override;
        void update(Timestep timestep) override;

        const std::string &name() const override { return m_name; }
        float sampleRate() const override { return m_sampleRate; }
        size_t channels() const override { return m_channels; }
        float bufferSize() const override { return m_bufferSize; }

    protected:
        static OSStatus AudioRenderCallback(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);

        std::shared_ptr<AudioBuffer> m_audioBuffer = nullptr;

        std::string m_name = "Uninitialized";
        float m_sampleRate = 0;
        size_t m_channels = 0;
        float m_bufferSize = 0;

        uint32_t m_currentFrame = 0;
        AudioDeviceID m_deviceID = 0;
        AudioComponentInstance m_audioUnit = nullptr;
    };
}
