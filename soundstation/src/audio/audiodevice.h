#pragma once

#include <memory>
#include <string>

#include "audio/audiobuffer.h"

#include "core/time.h"

namespace SoundStation {
    class AudioDevice {
    public:
        virtual ~AudioDevice() = default;
        virtual void setAudioBuffer(const std::shared_ptr<AudioBuffer>& audioBuffer) = 0;
        virtual void update(Timestep timestep) = 0;

        virtual const std::string& name() const = 0;
        virtual float sampleRate() const = 0;
        virtual size_t channels() const = 0;
        virtual float bufferSize() const = 0;

        static std::shared_ptr<AudioDevice> create();
    };
}