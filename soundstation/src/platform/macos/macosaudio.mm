#include "macosaudio.h"

#include "core/assert.h"

#include <filesystem>

namespace SoundStation {

    MacOSAudio::MacOSAudio(const std::string& path) 
        : m_path(path), m_playing(false), m_position(0.0f), m_duration(0.0f)
    {
        SS_ASSERT(std::filesystem::exists(path), fmt::format("Audio file {} does not exist", path));
        SS_LOG_INFO(fmt::format("Loading audio file {}", path));

        CFURLRef fileURL = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault, (const UInt8*)path.c_str(), path.size(), false);
        OSStatus result = AudioFileOpenURL(fileURL, kAudioFileReadPermission, 0, &(this->m_file));
        SS_ASSERT(result == noErr, "Failed to open audio file");

        // OSStatus AudioFileGetProperty(AudioFileID inAudioFile, AudioFilePropertyID inPropertyID, UInt32 *ioDataSize, void *outPropertyData);
        UInt32 packetCountSize = sizeof(UInt64);
        UInt64 packetCount = 0;
        result = AudioFileGetProperty(m_file, kAudioFilePropertyAudioDataPacketCount, &packetCountSize, &packetCount);
        SS_ASSERT(result == noErr, fmt::format("Failed to get audio file packet count. Was {}", result));

        AudioStreamBasicDescription format;
        UInt32 formatSize = sizeof(format);
        result = AudioFileGetProperty(m_file, kAudioFilePropertyDataFormat, &formatSize, &format);
        SS_ASSERT(result == noErr, fmt::format("Failed to get audio file format. Was {}", result));

        m_duration = (float)packetCount / format.mSampleRate;
    }

    MacOSAudio::~MacOSAudio() {
        AudioFileClose(m_file);
    }

    void MacOSAudio::play() {

    }
    void MacOSAudio::pause() {

    }
    void MacOSAudio::stop() {
  
        
    }

    void MacOSAudio::update() {
 
    }

    void MacOSAudio::seek(float position) {

    }

    float MacOSAudio::duration() const {
        return m_duration;
    }
    float MacOSAudio::position() const {
        return m_position;
    }

    bool MacOSAudio::playing() const {
        return m_playing;
    }

    std::shared_ptr<Audio> Audio::create(const std::string& path) {
        return std::make_shared<MacOSAudio>(path);
    }

}