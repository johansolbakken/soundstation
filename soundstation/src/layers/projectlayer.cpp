#include "projectlayer.h"

#include "core/application.h"

#include <imgui.h>

namespace SoundStation {

    ProjectLayer::ProjectLayer()
        : Layer("ProjectLayer")
    {
    }

    void ProjectLayer::onAttach()
    {
    }

    void ProjectLayer::onDetach()
    {
    }

    void ProjectLayer::onUpdate(Timestep t)
    {
    }

    void ProjectLayer::onUIRender()
    {
        ImGui::Begin("Project");
        ImGui::Text("Project Settings");
        ImGui::Separator();
        ImGui::InputText("Project Name", m_projectName, sizeof(m_projectName));
        ImGui::InputInt("Sample Rate", (int*)&m_sampleRate, 1, 100000);
        ImGui::End();
    }

}