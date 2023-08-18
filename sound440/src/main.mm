#include <Foundation/Foundation.h>
#include <AudioToolbox/AudioToolbox.h>

static OSStatus playbackCallback(void *inRefCon,
                                 AudioUnitRenderActionFlags *ioActionFlags,
                                 const AudioTimeStamp *inTimeStamp,
                                 UInt32 inBusNumber,
                                 UInt32 inNumberFrames,
                                 AudioBufferList *ioData) {
    
    const double amplitude = 0.5;
    const double sampleRate = 44100.0;
    const double frequency = 440.0;
    
    double theta = 0.0;
    double thetaIncrement = 2.0 * M_PI * frequency / sampleRate;
    
    for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
        const double sample = amplitude * sin(theta);
        
        for (UInt32 channel = 0; channel < ioData->mNumberBuffers; ++channel) {
            ((float *)ioData->mBuffers[channel].mData)[frame] = (float)sample;
        }
        
        theta += thetaIncrement;
        if (theta > 2.0 * M_PI) {
            theta -= 2.0 * M_PI;
        }
    }
    
    return noErr;
}


int main(int argc, const char * argv[]) {
    @autoreleasepool {
        AudioComponentDescription desc;
        desc.componentType = kAudioUnitType_Output;
        desc.componentSubType = kAudioUnitSubType_DefaultOutput;
        desc.componentManufacturer = kAudioUnitManufacturer_Apple;
        desc.componentFlags = 0;
        desc.componentFlagsMask = 0;

        AudioComponent component = AudioComponentFindNext(NULL, &desc);
        AudioUnit outputUnit;
        AudioComponentInstanceNew(component, &outputUnit);
        AudioUnitInitialize(outputUnit);

        AURenderCallbackStruct callbackStruct;
        callbackStruct.inputProc = playbackCallback;
        callbackStruct.inputProcRefCon = NULL;
        AudioUnitSetProperty(outputUnit,
                             kAudioUnitProperty_SetRenderCallback,
                             kAudioUnitScope_Global,
                             0,
                             &callbackStruct,
                             sizeof(callbackStruct));

        AudioStreamBasicDescription streamFormat;
        streamFormat.mSampleRate = 44100.0;
        streamFormat.mFormatID = kAudioFormatLinearPCM;
        streamFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
        streamFormat.mFramesPerPacket = 1;
        streamFormat.mChannelsPerFrame = 1;
        streamFormat.mBitsPerChannel = sizeof(float) * 8;
        streamFormat.mBytesPerFrame = sizeof(float);
        streamFormat.mBytesPerPacket = sizeof(float);

        AudioUnitSetProperty(outputUnit,
                             kAudioUnitProperty_StreamFormat,
                             kAudioUnitScope_Input,
                             0,
                             &streamFormat,
                             sizeof(streamFormat));

        AudioOutputUnitStart(outputUnit);

        // Run the audio playback for a certain duration (in seconds)
        sleep(5);

        AudioOutputUnitStop(outputUnit);
        AudioComponentInstanceDispose(outputUnit);
    }
    return 0;
}
