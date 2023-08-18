#include "macosaudiodevice.h"

#include <AudioToolbox/AudioToolbox.h>

#include "core/log.h"

namespace SoundStation {
    MacOSAudioDevice::MacOSAudioDevice() {
        // get a list of all the audio devices
        AudioObjectPropertyAddress propertyAddress = {
            kAudioHardwarePropertyDevices,
            kAudioObjectPropertyScopeGlobal,
        };

        UInt32 dataSize = 0;
        OSStatus status = AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &dataSize);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get audio device list size");
            return;
        }

        UInt32 deviceCount = dataSize / sizeof(AudioDeviceID);
        AudioDeviceID *deviceIDs = new AudioDeviceID[dataSize];
        status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &dataSize, deviceIDs);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get audio device list");
            return;
        }

        // get the default output device
        propertyAddress.mSelector = kAudioHardwarePropertyDefaultOutputDevice;
        AudioDeviceID defaultDeviceID;
        dataSize = sizeof(AudioDeviceID);
        status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &dataSize, &defaultDeviceID);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device");
            return;
        }

        // get the default output device's name
        propertyAddress.mSelector = kAudioDevicePropertyDeviceNameCFString;
        CFStringRef deviceName;
        dataSize = sizeof(CFStringRef);
        status = AudioObjectGetPropertyData(defaultDeviceID, &propertyAddress, 0, NULL, &dataSize, &deviceName);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device name");
            return;
        }
        m_name = CFStringGetCStringPtr(deviceName, kCFStringEncodingUTF8);

        // get the default output device's sample rate
        propertyAddress.mSelector = kAudioDevicePropertyNominalSampleRate;
        Float64 sampleRate;
        dataSize = sizeof(Float64);
        status = AudioObjectGetPropertyData(defaultDeviceID, &propertyAddress, 0, NULL, &dataSize, &sampleRate);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device sample rate");
            return;
        }
        m_sampleRate = sampleRate;

        // get the default output device's buffer size
        propertyAddress.mSelector = kAudioDevicePropertyBufferFrameSize;
        UInt32 bufferSize;
        dataSize = sizeof(UInt32);
        status = AudioObjectGetPropertyData(defaultDeviceID, &propertyAddress, 0, NULL, &dataSize, &bufferSize);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device buffer size");
            return;
        }
        m_bufferSize = bufferSize;

        // get the default output device's number of channels
        propertyAddress.mSelector = kAudioDevicePropertyStreamConfiguration;
        AudioBufferList *bufferList;
        dataSize = 0;
        status = AudioObjectGetPropertyDataSize(defaultDeviceID, &propertyAddress, 0, NULL, &dataSize);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device buffer list size");
            return;
        }

        bufferList = (AudioBufferList *)malloc(dataSize);
        status = AudioObjectGetPropertyData(defaultDeviceID, &propertyAddress, 0, NULL, &dataSize, bufferList);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device buffer list");
            return;
        }

        m_channels = bufferList->mNumberBuffers;
        free(bufferList);

        delete[] deviceIDs;
    }
    
    MacOSAudioDevice::~MacOSAudioDevice() {

    }
    
    void MacOSAudioDevice::setAudioBuffer(const std::shared_ptr<AudioBuffer> &audioBuffer) {
        m_audioBuffer = audioBuffer;
    }
    
    void MacOSAudioDevice::update() {

    }

    std::shared_ptr<AudioDevice> AudioDevice::create() {
        return std::make_shared<MacOSAudioDevice>();
    }
}