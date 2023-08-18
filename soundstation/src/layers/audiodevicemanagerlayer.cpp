#include "audiodevicemanagerlayer.h"

#include <imgui.h>

namespace SoundStation
{
    AudioDeviceManagerLayer::AudioDeviceManagerLayer()
        : Layer("Audio Device Manager")
    {
        m_audioDevice = AudioDevice::create();
    }

    void AudioDeviceManagerLayer::onAttach()
    {
    }

    void AudioDeviceManagerLayer::onDetach()
    {
    }

    void AudioDeviceManagerLayer::onUpdate(Timestep step)
    {
    }

    void AudioDeviceManagerLayer::onUIRender()
    {
        ImGui::Begin("Audio Device");
        ImGui::Text("Name: %s", m_audioDevice->name().c_str());
        ImGui::Text("Sample Rate: %f", m_audioDevice->sampleRate());
        ImGui::Text("Channels: %zu", m_audioDevice->channels());
        ImGui::Text("Buffer Size: %f", m_audioDevice->bufferSize());
        ImGui::End();
    }
}