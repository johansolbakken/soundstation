#include "macosaudiodevice.h"

#include <AudioToolbox/AudioToolbox.h>

#include "core/log.h"

namespace SoundStation {

    OSStatus MacOSAudioDevice::AudioRenderCallback(void* inRefCon,
                             AudioUnitRenderActionFlags* ioActionFlags,
                             const AudioTimeStamp* inTimeStamp,
                             UInt32 inBusNumber,
                             UInt32 inNumberFrames,
                             AudioBufferList* ioData) {
        MacOSAudioDevice* audioDevice = static_cast<MacOSAudioDevice*>(inRefCon);
        float* outputBuffer = static_cast<float*>(ioData->mBuffers[0].mData);

        if (audioDevice->m_audioBuffer == nullptr) {
            audioDevice->m_currentFrame = 0;
            return noErr;
        }

        size_t channels = audioDevice->m_audioBuffer->channels();
        auto data = reinterpret_cast<const float(*)[2]>(audioDevice->m_audioBuffer->data());
        float sampleRate = audioDevice->m_audioBuffer->sampleRate();
        AudioBufferFormat format = audioDevice->m_audioBuffer->format();

        if (audioDevice->m_currentFrame >= audioDevice->m_audioBuffer->size()) {
            return noErr;
        }

        SS_LOG_DEBUG(fmt::format("Playing audio buffer at cursor: {}", audioDevice->m_currentFrame));

        for (int i = 0; i < inNumberFrames; i++) {
            for (int j = 0; j < channels; j++) {
                float sample = data[audioDevice->m_currentFrame][j];
                if (format == AudioBufferFormat::Float32Bit) {
                    sample *= 0.5f;
                }
                outputBuffer[i * channels + j] = sample;
            }
            audioDevice->m_currentFrame++;
        }

        return noErr;
    }

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

        // Create an audio unit
        AudioComponentDescription componentDescription;
        componentDescription.componentType = kAudioUnitType_Output;
        componentDescription.componentSubType = kAudioUnitSubType_DefaultOutput;
        componentDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
        componentDescription.componentFlags = 0;
        componentDescription.componentFlagsMask = 0;

        AudioComponent component = AudioComponentFindNext(NULL, &componentDescription);
        status = AudioComponentInstanceNew(component, &m_audioUnit);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to create audio unit");
            return;
        }


        // Set the format to 32 bit float, linear PCM
        AudioStreamBasicDescription streamDescription;
        streamDescription.mSampleRate = m_sampleRate;
        streamDescription.mFormatID = kAudioFormatLinearPCM;
        streamDescription.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
        streamDescription.mBytesPerPacket = sizeof(float);
        streamDescription.mFramesPerPacket = 1;
        streamDescription.mBytesPerFrame = sizeof(float);
        streamDescription.mChannelsPerFrame = 2;
        streamDescription.mBitsPerChannel = sizeof(float) * 8;
        status = AudioUnitSetProperty(m_audioUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &streamDescription, sizeof(streamDescription));
        if (status != noErr) {
            SS_LOG_ERROR("Failed to set audio unit stream format");
            return;
        }

        // Set the render callback
        AURenderCallbackStruct callbackStruct;
        callbackStruct.inputProc = AudioRenderCallback;
        callbackStruct.inputProcRefCon = this;
        status = AudioUnitSetProperty(m_audioUnit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &callbackStruct, sizeof(callbackStruct));
        if (status != noErr) {
            SS_LOG_ERROR("Failed to set audio unit callback");
            return;
        }

        // Initialize the audio unit
        status = AudioUnitInitialize(m_audioUnit);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to initialize audio unit");
            return;
        }

        // Start the audio unit
        status = AudioOutputUnitStart(m_audioUnit);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to start audio unit");
            return;
        }

        delete[] deviceIDs;
    }
    
    MacOSAudioDevice::~MacOSAudioDevice() {

    }
    
    void MacOSAudioDevice::setAudioBuffer(const std::shared_ptr<AudioBuffer> &audioBuffer) {
        m_audioBuffer = audioBuffer;
    }
    
    void MacOSAudioDevice::update(Timestep delta) {        
        static int cursor = 0;

        if (m_audioBuffer == nullptr) {
            return;
        }
    }

    std::shared_ptr<AudioDevice> AudioDevice::create() {
        return std::make_shared<MacOSAudioDevice>();
    }
}