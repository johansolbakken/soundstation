#include "audiodevicemanagerlayer.h"

#include <imgui.h>

#include "core/log.h"

namespace SoundStation
{
    AudioDeviceManagerLayer::AudioDeviceManagerLayer()
        : Layer("Audio Device Manager")
    {
        m_audioDeviceList = AudioDeviceList::create();
    }

    void AudioDeviceManagerLayer::onAttach()
    {
        m_audioDeviceList->onUpdate();
    }

    void AudioDeviceManagerLayer::onDetach()
    {
    }

    void AudioDeviceManagerLayer::onUpdate(Timestep step)
    {
    }

    void AudioDeviceManagerLayer::onUIRender()
    {
        if (m_audioDevice != nullptr)
        {
            ImGui::Begin("Audio Device");
            ImGui::Text("Name: %s", m_audioDevice->name().c_str());
            ImGui::Text("Sample Rate: %f", m_audioDevice->sampleRate());
            ImGui::Text("Channels: %zu", m_audioDevice->channels());
            ImGui::Text("Buffer Size: %f", m_audioDevice->bufferSize());
            ImGui::End();
        }

        ImGui::Begin("Audio Device Manager");

        if (m_activeOutputDevice != -1)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0));
            ImGui::Text("Output Device: %s", m_activeOutputDeviceName.c_str());
            ImGui::PopStyleColor();
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0));
            ImGui::Text("Output Device: None");
            ImGui::PopStyleColor();
        }

        ImGui::Text("Available Output Devices:");
        ImGui::Separator();

        auto outputDevices = m_audioDeviceList->outputDevices();

        // Use a separate flag variable for tracking selection
        bool deviceSelected = false;

        for (auto &device : outputDevices)
        {
            // Use an identifier for each selectable item to avoid conflicts
            std::string id = device.second + std::to_string(device.first);
            std::string deviceName = device.second.c_str();

            SS_LOG_DEBUG(fmt::format("Device: {}", deviceName));

            ImGui::PushID(id.c_str());

            if (ImGui::Selectable(deviceName.c_str(), m_selectedOutputDevice == device.first))
            {
                // Update the selected device when it's clicked
                m_selectedOutputDevice = device.first;
                deviceSelected = true; // Set the flag to true

                SS_LOG_DEBUG(fmt::format("Selected device: {}", deviceName));
            }
            ImGui::PopID();
        }

        // only clickable if devices are available

        if (ImGui::Button("Select"))
        {
            m_activeOutputDevice = m_selectedOutputDevice;
            m_activeOutputDeviceName = outputDevices[m_activeOutputDevice];
        }

        if (ImGui::Button("Refresh"))
        {
            m_audioDeviceList->onUpdate();
        }

        ImGui::End();
    }
}
