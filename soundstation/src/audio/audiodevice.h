#pragma once

namespace SoundStation
{
    using AudioCallback = std::function<void(float *left, float *right, uint32_t frames)>;

    class AudioDevice
    {
    public:
        virtual ~AudioDevice() = default;

        virtual const std::string &name() const = 0;
        virtual float sampleRate() const = 0;
        virtual size_t channels() const = 0;
        virtual float bufferSize() const = 0;

        virtual uint32_t id() const = 0;

        virtual void setAudioCallback(const AudioCallback &callback) = 0;

        static std::shared_ptr<AudioDevice> create(uint32_t id);
    };
}