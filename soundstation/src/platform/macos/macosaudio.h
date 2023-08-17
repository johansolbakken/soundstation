#pragma once

#include "audio/audio.h"

#include <CoreAudio/CoreAudio.h>
#include <AudioToolbox/AudioToolbox.h>
#include <AudioToolbox/AudioFile.h>
#include <AudioToolbox/AudioQueue.h>

namespace SoundStation
{
    class MacOSAudio : public Audio
    {
    public:
        MacOSAudio(const std::string &path);
        ~MacOSAudio() override;

        void play() override;
        void pause() override;

        void update() override;

        void seek(float position) override;

        float duration() const override;
        float position() const override;

        bool playing() const override;

    private:
        std::string m_path;

        float m_duration = 0.0;
        float m_position = 0.0;

        bool m_playing = false;

        AudioFileID m_file = nullptr;
        AudioQueueRef m_audioQueue = nullptr;
        const int kBufferSize = 4096;
        static constexpr int kBufferCount = 3;
        AudioQueueBufferRef m_audioQueueBuffers[kBufferCount]; // You can adjust the buffer count as needed
    };
}