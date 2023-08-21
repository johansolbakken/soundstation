#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "core/time.h"
#include "core/log.h"

#include "audio/audiodevice.h"

#include <AudioToolbox/AudioToolbox.h>

namespace SoundStation
{
    class MacOSAudioDevice : public AudioDevice
    {
    public:
        MacOSAudioDevice(uint32_t deviceID);
        ~MacOSAudioDevice() override;

        const std::string &name() const override { return m_name; }
        float sampleRate() const override { return m_sampleRate; }
        size_t channels() const override { return m_channels; }
        float bufferSize() const override { return m_bufferSize; }

        uint32_t id() const override { return m_deviceID; }

        void setAudioCallback(const AudioCallback &callback) override { m_callback = callback; }

    protected:
        static OSStatus AudioRenderCallback(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);

        std::string m_name = "Uninitialized";
        float m_sampleRate = 0;
        size_t m_channels = 0;
        float m_bufferSize = 0;

        AudioDeviceID m_deviceID = 0;
        AudioComponentInstance m_audioUnit = nullptr;

        AudioCallback m_callback;
    };
}
