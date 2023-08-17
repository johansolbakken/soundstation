#pragma once

#include <memory>
#include <string>

namespace SoundStation
{
    class Audio
    {
    public:
        virtual ~Audio() = default;

        virtual void play() = 0;
        virtual void pause() = 0;

        virtual void update() = 0;

        virtual void seek(float position) = 0;

        virtual float duration() const = 0;
        virtual float position() const = 0;

        virtual bool playing() const = 0;

        static std::shared_ptr<Audio> create(const std::string &path);
    };
}