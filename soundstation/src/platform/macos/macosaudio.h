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
        void stop() override;

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
        AudioQueueBufferRef m_audioQueueBuffers[3]; // You can adjust the buffer count as needed
    };
}