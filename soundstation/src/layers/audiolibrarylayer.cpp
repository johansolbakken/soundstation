#include "audiolibrarylayer.h"

#include <imgui.h>

#include "core/log.h"
#include "core/application.h"

#include "layers/playerlayer.h"

namespace SoundStation{

    AudioLibraryLayer::AudioLibraryLayer()
    : Layer("AudioLibraryLayer")
    {
    }

    void AudioLibraryLayer::onUIRender()
    {
        ImGui::Begin("Audio Library");
        ImGui::Text("Audio Library");
        ImGui::Separator();

        for (auto& file : m_audioFiles)
        {
            if (ImGui::Selectable(file->filename().c_str()))
            {
                
            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::Selectable("Open in Player"))
                {
                    auto playerLayer = static_cast<PlayerLayer*>(Application::instance().getLayer("PlayerLayer"));
                    if (playerLayer) {
                        playerLayer->setAudioFile(file);
                    } else {
                        SS_LOG_ERROR("Could not find PlayerLayer");
                    }
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