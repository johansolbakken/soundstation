#include "macosaudiodevicelist.h"

#include <CoreAudio/CoreAudio.h>
#include <CoreFoundation/CoreFoundation.h>

#include "core/assert.h"

namespace SoundStation {

     void MacOSAudioDeviceList::onUpdate() {
        m_inputDevices.clear();
        m_outputDevices.clear();

        // Add output id, name pairs

        AudioObjectPropertyAddress propertyAddress = {
            kAudioHardwarePropertyDevices,
            kAudioObjectPropertyScopeGlobal,
            kAudioObjectPropertyElementMain
        };

        UInt32 dataSize = 0;
        OSStatus status = AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &dataSize);
        SS_ASSERT(status == noErr, "Failed to get audio device count");

        UInt32 deviceCount = dataSize / sizeof(AudioDeviceID);
        AudioDeviceID *deviceIDs = new AudioDeviceID[deviceCount];
        status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, nullptr, &dataSize, deviceIDs);
        SS_ASSERT(status == noErr, "Failed to get audio device ids");

        for (UInt32 i = 0; i < deviceCount; ++i) {
            AudioDeviceID deviceID = deviceIDs[i];

            propertyAddress.mSelector = kAudioDevicePropertyDeviceNameCFString;
            CFStringRef deviceName = nullptr;
            dataSize = sizeof(deviceName);
            status = AudioObjectGetPropertyData(deviceID, &propertyAddress, 0, nullptr, &dataSize, &deviceName);
            SS_ASSERT(status == noErr, "Failed to get audio device name");

            propertyAddress.mSelector = kAudioDevicePropertyStreams;
            AudioStreamID *streamIDs = nullptr;
            dataSize = 0;
            status = AudioObjectGetPropertyDataSize(deviceID, &propertyAddress, 0, nullptr, &dataSize);
            SS_ASSERT(status == noErr, "Failed to get audio device stream count");

            UInt32 streamCount = dataSize / sizeof(AudioStreamID);
            streamIDs = new AudioStreamID[streamCount];
            status = AudioObjectGetPropertyData(deviceID, &propertyAddress, 0, nullptr, &dataSize, streamIDs);
            SS_ASSERT(status == noErr, "Failed to get audio device stream ids");

            for (UInt32 j = 0; j < streamCount; ++j) {
                AudioStreamID streamID = streamIDs[j];

                propertyAddress.mSelector = kAudioStreamPropertyDirection;
                AudioObjectPropertyScope scope = kAudioObjectPropertyScopeGlobal;
                AudioObjectPropertyElement element = kAudioObjectPropertyElementMain;
                UInt32 direction = 0;
                dataSize = sizeof(direction);
                status = AudioObjectGetPropertyData(streamID, &propertyAddress, 0, nullptr, &dataSize, &direction);
                SS_ASSERT(status == noErr, "Failed to get audio stream direction");

                uint32_t cDeviceId = uint32_t(deviceID);

                CFIndex length = CFStringGetLength(deviceName);
                char buffer[length + 1];
                memset(buffer, 0, sizeof(buffer));
                CFStringGetCString(deviceName, buffer, sizeof(buffer), kCFStringEncodingUTF8);

                std::string cDeviceName =  buffer;

                if (cDeviceName.empty()) {
                    continue;
                }

                enum class Direction : uint32_t {
                    Output = 0,
                    Input = 1,
                };

                if (uint32_t(direction) == uint32_t(Direction::Input)) {
                    m_inputDevices[cDeviceId] = cDeviceName;
                } else if (uint32_t(direction) == uint32_t(Direction::Output)) {
                    m_outputDevices[cDeviceId] = cDeviceName;
                }
            }

            delete[] streamIDs;
        }

        delete[] deviceIDs;
     }

     std::shared_ptr<AudioDeviceList> AudioDeviceList::create() {
         return std::make_shared<MacOSAudioDeviceList>();
     }

}
