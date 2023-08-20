#include "macosaudiodevice.h"

#include <AudioToolbox/AudioToolbox.h>

#include "core/log.h"
#include "core/assert.h"

namespace SoundStation {

    OSStatus MacOSAudioDevice::AudioRenderCallback(void* inRefCon,
                             AudioUnitRenderActionFlags* ioActionFlags,
                             const AudioTimeStamp* inTimeStamp,
                             UInt32 inBusNumber,
                             UInt32 inNumberFrames,
                             AudioBufferList* ioData) {
        MacOSAudioDevice* audioDevice = static_cast<MacOSAudioDevice*>(inRefCon);
        float* outputBufferLeft = static_cast<float*>(ioData->mBuffers[0].mData);
        float* outputBufferRight = static_cast<float*>(ioData->mBuffers[1].mData);

        if (!audioDevice->m_playing || audioDevice->m_audioBuffer == nullptr) {

            for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
                outputBufferLeft[frame] = 0.0f; // Left channel
                outputBufferRight[frame] = 0.0f; // Right channel
            }

            return noErr;
        }   

        if (audioDevice->m_currentFrame >= audioDevice->m_audioBuffer->frames()) {
            if (audioDevice->m_playing) {
                audioDevice->stop();
            }

            for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
                outputBufferLeft[frame] = 0.0f; // Left channel
                outputBufferRight[frame] = 0.0f; // Right channel
            }

            return noErr;
        }

        size_t channels = audioDevice->m_audioBuffer->channels();
        auto data = reinterpret_cast<const float(*)[2]>(audioDevice->m_audioBuffer->data());
        float sampleRate = audioDevice->m_audioBuffer->sampleRate();

        SS_ASSERT(ioData->mNumberBuffers == 2, "Expected 2 buffers");

        for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
            if (audioDevice->m_currentFrame >= audioDevice->m_audioBuffer->frames()) {
                outputBufferLeft[frame] = 0.0f; // Left channel
                outputBufferRight[frame] = 0.0f; // Right channel
                continue;
            }

            const float* sample = data[audioDevice->m_currentFrame];
            outputBufferLeft[frame] = sample[0];
            outputBufferRight[frame] = sample[1];
            audioDevice->m_currentFrame++;
        }

        return noErr;
    }


    MacOSAudioDevice::MacOSAudioDevice(uint32_t deviceId) {
        AudioObjectPropertyAddress propertyAddress = {
            kAudioHardwarePropertyDevices,
            kAudioObjectPropertyScopeGlobal,
            kAudioObjectPropertyElementMain
        };

        AudioDeviceID deviceID = deviceId;

        // check if device id is valid
        UInt32 dataSize = 0;
        OSStatus status = AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &dataSize);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get audio device count");
            return;
        }

        UInt32 deviceCount = dataSize / sizeof(AudioDeviceID);
        AudioDeviceID *deviceIDs = new AudioDeviceID[deviceCount];
        status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &dataSize, deviceIDs);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get audio device ids");
            return;
        }

        bool found = false;
        for (UInt32 i = 0; i < deviceCount; ++i) {
            if (deviceIDs[i] != deviceID) {
                continue;
            }

            found = true;
        }

        if (!found) {
            SS_LOG_ERROR("Invalid audio device id");
            return;
        }

        // Get the device name
        propertyAddress.mSelector = kAudioDevicePropertyDeviceNameCFString;
        CFStringRef deviceName = nullptr;
        dataSize = sizeof(deviceName);
        status = AudioObjectGetPropertyData(deviceID, &propertyAddress, 0, nullptr, &dataSize, &deviceName);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get audio device name");
            return;
        }
        m_name = CFStringGetCStringPtr(deviceName, kCFStringEncodingUTF8);

        // Get the sample rate
        propertyAddress.mSelector = kAudioDevicePropertyNominalSampleRate;
        Float64 sampleRate = 0;
        dataSize = sizeof(sampleRate);
        status = AudioObjectGetPropertyData(deviceID, &propertyAddress, 0, nullptr, &dataSize, &sampleRate);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get audio device sample rate");
            return;
        }
        m_sampleRate = sampleRate;
        
        // Get the buffer size
        propertyAddress.mSelector = kAudioDevicePropertyBufferFrameSize;
        UInt32 bufferSize = 0;
        dataSize = sizeof(bufferSize);
        status = AudioObjectGetPropertyData(deviceID, &propertyAddress, 0, nullptr, &dataSize, &bufferSize);
        if (status != noErr) {
            SS_LOG_ERROR("Failed to get audio device buffer size");
            return;
        }
        m_bufferSize = bufferSize;
        
        // Get the number of channels
        // todo(johan)

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
        AudioOutputUnitStop(m_audioUnit);
        AudioUnitUninitialize(m_audioUnit);
        AudioComponentInstanceDispose(m_audioUnit);
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

    std::shared_ptr<AudioDevice> AudioDevice::create(uint32_t deviceId) {
        return std::make_shared<MacOSAudioDevice>(deviceId);
    }
}