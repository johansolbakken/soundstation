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
        selectOutputDevice(m_audioDeviceList->defaultOutputDeviceId());
    }

    void AudioDeviceManagerLayer::onDetach()
    {
    }

    void AudioDeviceManagerLayer::onUpdate(Timestep step)
    {
    }

    void AudioDeviceManagerLayer::onUIRender()
    {
        if (!m_showAudioDeviceManager)
            return;

        if (m_audioDevice != nullptr)
        {
            ImGui::Begin("Audio Device");
            ImGui::Text("Name: %s", m_audioDevice->name().c_str());
            ImGui::Text("Sample Rate: %f", m_audioDevice->sampleRate());
            ImGui::Text("Channels: %zu", m_audioDevice->channels());
            ImGui::Text("Buffer Size: %f", m_audioDevice->bufferSize());
            ImGui::End();
        }

        ImGui::Begin("Audio Device Manager", &m_showAudioDeviceManager);

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

        for (auto &device : outputDevices)
        {
            // Use an identifier for each selectable item to avoid conflicts
            std::string id = device.second + std::to_string(device.first);
            std::string deviceName = device.second.c_str();

            ImGui::PushID(id.c_str());
            if (ImGui::Selectable(deviceName.c_str(), m_selectedOutputDevice == device.first))
                m_selectedOutputDevice = device.first;
            ImGui::PopID();
        }

        if (ImGui::Button("Select"))
            selectOutputDevice(m_selectedOutputDevice);

        if (ImGui::Button("Refresh"))
            m_audioDeviceList->onUpdate();

        ImGui::End();
    }

    void AudioDeviceManagerLayer::selectOutputDevice(uint32_t id)
    {
        m_audioDevice = nullptr;

        auto outputDevices = m_audioDeviceList->outputDevices();
        m_activeOutputDevice = id;
        m_activeOutputDeviceName = outputDevices[id];
        m_audioDevice = AudioDevice::create(id);
    }
}
