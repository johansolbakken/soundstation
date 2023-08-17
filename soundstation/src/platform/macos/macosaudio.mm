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

        // Create the audio queue

        auto audioQueueOutputCallback = [](void* inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer) {
            MacOSAudio* audio = (MacOSAudio*)inUserData;
            audio->update();
        };

        result = AudioQueueNewOutput(&format, audioQueueOutputCallback, this, nullptr, nullptr, 0, &(this->m_audioQueue));
        SS_ASSERT(result == noErr, fmt::format("Failed to create audio queue. Was {}", result));

        // Create the audio queue buffers
        for (int i = 0; i < kBufferCount; ++i) {
            result = AudioQueueAllocateBuffer(m_audioQueue, kBufferSize, &(this->m_audioQueueBuffers[i]));
            SS_ASSERT(result == noErr, fmt::format("Failed to allocate audio queue buffer. Was {}", result));
        }

        // Prime the audio queue with some data before starting
        this->update();
    }

    MacOSAudio::~MacOSAudio() {
        AudioQueueDispose(m_audioQueue, true);

        // Close the audio file
        AudioFileClose(m_file);

        // Free the audio queue buffers
        for (int i = 0; i < kBufferCount; ++i) {
            AudioQueueFreeBuffer(m_audioQueue, m_audioQueueBuffers[i]);
        }
    }

    void MacOSAudio::play() {
        m_playing = true;

    }

    void MacOSAudio::pause() {
        m_playing = false;
    }

    void MacOSAudio::update() {
        if (!m_playing) {
            // If not playing, there's no need to update the audio queue
            return;
        }

        if (m_position >= m_duration) {
            // If we've reached the end of the audio file, stop playback
            m_playing = false;
            return;
        }

        // Loop through the audio queue buffers and fill them with audio data
        for (int i = 0; i < kBufferCount; ++i) {
            // Read audio packet data from the file and copy it into the buffer
            UInt32 numPackets = kBufferSize; // Adjust as needed
            UInt32 numBytes = 0; // Placeholder for the number of bytes read

            // Dummy packet descriptions array (not used)
            AudioStreamPacketDescription packetDescriptions[numPackets];

            OSStatus result = AudioFileReadPacketData(m_file, false, &numBytes, packetDescriptions, m_position, &numPackets, m_audioQueueBuffers[i]);

            if (result != noErr) {
                // Handle error
                CFStringRef errorString = nullptr;
                switch (result) {
                    case kAudioFileUnsupportedFileTypeError:
                        SS_LOG_ERROR("Unsupported file type");
                        break;
                    case kAudioFileUnspecifiedError:
                        SS_LOG_ERROR("Unspecified error");
                        break;
                    default:
                        SS_LOG_ERROR(fmt::format("Failed to read audio file packet data. Was {}", result));
                        break;
                }
                // Additional error handling steps if needed
            }

            // Enqueue the buffer into the audio queue
            result = AudioQueueEnqueueBuffer(m_audioQueue, m_audioQueueBuffers[i], 0, nullptr);

            if (result != noErr) {
                // Handle error
                // Similar to above, you might stop playback or take appropriate action
                SS_LOG_ERROR(fmt::format("Failed to enqueue audio buffer. Was {}", result));
            }

            // Update the current position in the audio file
            m_position += numPackets;
        }
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