#include "pch.h"
#include "audiolibrarylayer.h"

#include <imgui.h>

#include "core/application.h"

#include "layers/playerlayer.h"

namespace SoundStation
{

    AudioLibraryLayer::AudioLibraryLayer()
        : Layer(staticName())
    {
    }

    void AudioLibraryLayer::onUIRender()
    {
        ImGui::Begin("Audio Library");
        ImGui::Text("Audio Library");
        ImGui::Separator();

        for (auto &file : m_audioFiles)
        {
            if (ImGui::Selectable(file->filename().c_str()))
            {
            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::Selectable("Open in Player"))
                {
                    if (auto playerLayer = Application::getLayer<PlayerLayer>())
                        playerLayer->setAudioFile(file);
                }

                if (ImGui::Selectable("Set as mixer source"))
                {
                    if (auto mixerLayer = Application::getLayer<MixerLayer>())
                        mixerLayer->setAudioFile(file);
                }

                ImGui::EndPopup();
            }
        }

        static bool m_showLoadAudioFileModal = false;
        if (m_showLoadAudioFileModal)
        {
            ImGui::OpenPopup("Load Audio File");
            m_showLoadAudioFileModal = false;
        }

        if (ImGui::Button("Load Audio File"))
        {
            m_showLoadAudioFileModal = true;
        }

        if (ImGui::BeginPopupModal("Load Audio File", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            static char m_filePath[256] = {0};
            ImGui::InputText("File Path", m_filePath, 256);

            if (ImGui::Button("Load"))
            {
                m_audioFiles.push_back(AudioFile::create(m_filePath));
                m_showLoadAudioFileModal = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("Cancel"))
            {
                m_showLoadAudioFileModal = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }
}