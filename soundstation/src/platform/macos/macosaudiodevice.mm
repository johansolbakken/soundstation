#include "macosaudiodevice.h"

#include <AudioToolbox/AudioToolbox.h>

#include "core/log.h"

namespace SoundStation {
    MacOSAudioDevice::MacOSAudioDevice() {
        // get a list of all the audio devices
        AudioObjectPropertyAddress propertyAddress = {
            kAudioHardwarePropertyDevices,
            kAudioObjectPropertyScopeGlobal,
            kAudioObjectPropertyElementMain
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
        dataSize = sizeof(AudioDeviceID);
        status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &dataSize, &m_deviceID);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device");
            return;
        }

        // get the default output device's name
        propertyAddress.mSelector = kAudioDevicePropertyDeviceNameCFString;
        CFStringRef deviceName;
        dataSize = sizeof(CFStringRef);
        status = AudioObjectGetPropertyData(m_deviceID, &propertyAddress, 0, NULL, &dataSize, &deviceName);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device name");
            return;
        }
        m_name = CFStringGetCStringPtr(deviceName, kCFStringEncodingUTF8);

        // get the default output device's sample rate
        propertyAddress.mSelector = kAudioDevicePropertyNominalSampleRate;
        Float64 sampleRate;
        dataSize = sizeof(Float64);
        status = AudioObjectGetPropertyData(m_deviceID, &propertyAddress, 0, NULL, &dataSize, &sampleRate);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device sample rate");
            return;
        }
        m_sampleRate = sampleRate;

        // get the default output device's buffer size
        propertyAddress.mSelector = kAudioDevicePropertyBufferFrameSize;
        UInt32 bufferSize;
        dataSize = sizeof(UInt32);
        status = AudioObjectGetPropertyData(m_deviceID, &propertyAddress, 0, NULL, &dataSize, &bufferSize);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get default audio device buffer size");
            return;
        }
        m_bufferSize = bufferSize;

        // get the default output device's number of channels
        // todo()

        delete[] deviceIDs;
    }
    
    MacOSAudioDevice::~MacOSAudioDevice() {

    }
    
    void MacOSAudioDevice::setAudioBuffer(const std::shared_ptr<AudioBuffer> &audioBuffer) {
        m_audioBuffer = audioBuffer;
    }
    
    void MacOSAudioDevice::update(Timestep delta) {
        if (m_audioBuffer == nullptr) {
            return;
        }

        static int cursor = 0;

        size_t channels = m_audioBuffer->channels();
        auto data = reinterpret_cast<float(*)[2]>(m_audioBuffer->data());
        float sampleRate = m_audioBuffer->sampleRate();
        AudioBufferFormat format = m_audioBuffer->format();
        
        // read from the audio buffer and write to the output device
        AudioBufferList bufferList;
        bufferList.mNumberBuffers = channels;
        for (int i = 0; i < channels; i++) {
            bufferList.mBuffers[i].mNumberChannels = 1;
            bufferList.mBuffers[i].mDataByteSize = m_bufferSize * sizeof(float);
            bufferList.mBuffers[i].mData = data[cursor];
        }

        AudioTimeStamp timeStamp;
        memset(&timeStamp, 0, sizeof(AudioTimeStamp));
/*
        OSStatus status = AudioDeviceWrite(m_deviceID, &timeStamp, &bufferList);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to write to audio device");
            return;
        }
*/
        cursor += m_bufferSize;

        if (cursor >= m_audioBuffer->size()) {
            cursor = 0;
        }
    }

    std::shared_ptr<AudioDevice> AudioDevice::create() {
        return std::make_shared<MacOSAudioDevice>();
    }
}