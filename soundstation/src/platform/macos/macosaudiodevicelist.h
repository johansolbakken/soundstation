#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "core/time.h"
#include "core/log.h"

#include "audio/audiodevicelist.h"

namespace SoundStation
{
    class MacOSAudioDeviceList : public AudioDeviceList
    {
    public:
        MacOSAudioDeviceList() = default;
        ~MacOSAudioDeviceList() override = default;

        void onUpdate() override;

        const std::map<uint32_t, std::string> &inputDevices() const override { return m_inputDevices; }
        const std::map<uint32_t, std::string> &outputDevices() const override { return m_outputDevices; }

        uint32_t defaultOutputDeviceId() const override;

    private:
        std::map<uint32_t, std::string> m_inputDevices;
        std::map<uint32_t, std::string> m_outputDevices;
    };
}