#include "audiodevicemanagerlayer.h"

#include <imgui.h>

#include "core/log.h"

namespace SoundStation
{
    AudioDeviceManagerLayer::AudioDeviceManagerLayer()
        : Layer("Audio Device Manager")
    {
        m_audioDevice = AudioDevice::create();

        m_availableDevices[0] = "Default";
        m_availableDevices[1] = "Default";
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

        ImGui::Begin("Audio Device Manager");

        ImGui::Text("Available Devices:");
        ImGui::Separator();

        // Use a separate flag variable for tracking selection
        bool deviceSelected = false;

        for (auto &device : m_availableDevices)
        {
            // Use an identifier for each selectable item to avoid conflicts
            const char *deviceName = device.second.c_str();

            ImGui::PushID(deviceName + device.first);
            if (ImGui::Selectable(deviceName, m_selectedDevice == device.first))
            {
                // Update the selected device when it's clicked
                m_selectedDevice = device.first;
                deviceSelected = true; // Set the flag to true

                SS_LOG_DEBUG(fmt::format("Selected device: {}", deviceName));
            }
            ImGui::PopID();
        }

        // Show a message if no device is selected
        if (!deviceSelected)
        {
            ImGui::Text("Please select a device.");
        }

        ImGui::End();
    }
}