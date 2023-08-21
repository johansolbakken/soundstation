#pragma once

namespace SoundStation
{
    class AudioDeviceList
    {
    public:
        virtual ~AudioDeviceList() = default;

        virtual void onUpdate() = 0;

        virtual const std::map<uint32_t, std::string> &inputDevices() const = 0;
        virtual const std::map<uint32_t, std::string> &outputDevices() const = 0;

        virtual uint32_t defaultOutputDeviceId() const = 0;

        static std::shared_ptr<AudioDeviceList> create();
    };
}