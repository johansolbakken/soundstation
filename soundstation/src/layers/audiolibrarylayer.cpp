#include "audiolibrarylayer.h"

#include <imgui.h>

namespace SoundStation{

    AudioLibraryLayer::AudioLibraryLayer()
    : Layer("AudioLibraryLayer")
    {
    }

    void AudioLibraryLayer::onAttach()
    {
        m_audioFiles.push_back(AudioFile::create("assets/sound/Lizza Bizzaz.aif"));
    }

    void AudioLibraryLayer::onDetach()
    {
    }

    void AudioLibraryLayer::onUpdate(Timestep t)
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
        }

        ImGui::End();
    }
}