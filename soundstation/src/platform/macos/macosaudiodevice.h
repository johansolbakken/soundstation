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

        uint32_t id() const override { return m_deviceID; }
        uint32_t currentFrame() const override { return m_currentFrame; }
        void incrementCurrentFrame() { m_currentFrame++; }
        void setCurrentFrame(uint32_t frame) { m_currentFrame = frame; }

        void seek(uint32_t frame) override { m_currentFrame = frame; }

        bool isPlaying() const override { return m_playing; }
        void play() override { m_playing = true; }
        void pause() override { m_playing = false; }
        void stop() override { m_playing = false; m_currentFrame = 0; }

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

        bool m_playing = false;
    };
}
