#include "projectlayer.h"

#include "core/application.h"
#include "core/platform.h"

#include "serializer/serializer.h"

#include "layers/audiolibrarylayer.h"

#include <imgui.h>

namespace SoundStation
{

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
        if (!m_open)
            return;

        ImGui::Begin("Project", &m_open);
        ImGui::Text("Project Settings");
        ImGui::Separator();

        if (ImGui::InputText("Project Name", m_projectName, sizeof(m_projectName)))
        {
            m_projectNameChanged = true;
        }
        else if (m_projectNameChanged && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
        {
            m_projectNameChanged = false;
            m_project.setName(m_projectName);
        }

        if (ImGui::InputInt("Sample Rate", (int *)&m_sampleRate, 1, 100000))
        {
            m_sampleRateChanged = true;
        }
        else if (m_sampleRateChanged && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
        {
            m_sampleRateChanged = false;
            m_project.setSampleRate(m_sampleRate);
        }

        ImGui::End();
    }

    void ProjectLayer::saveProject()
    {
        if (m_project.path().empty())
        {
            saveProjectAs();
            return;
        }

        Serializer serializer;

        serializer.setProject(m_project);

        auto audioLibrary = static_cast<AudioLibraryLayer *>(Application::instance().getLayer("AudioLibraryLayer"));
        if (audioLibrary)
        {
            serializer.setAudioFiles(audioLibrary->audioFiles());
        }

        serializer.serialize(m_project.path());
    }

    void ProjectLayer::saveProjectAs()
    {
        auto path = Platform::saveFile("ssp");
        if (path.empty())
            return;

        m_project.setPath(path);
        saveProject();
    }

    void ProjectLayer::openProject()
    {
        auto path = Platform::openFile("ssp");
        if (path.empty())
            return;

        Serializer serializer;
        serializer.deserialize(path);

        m_project = serializer.project();
        memset(m_projectName, 0, sizeof(m_projectName));
        strcpy(m_projectName, m_project.name().c_str());

        m_sampleRate = m_project.sampleRate();

        auto audioLibrary = static_cast<AudioLibraryLayer *>(Application::instance().getLayer("AudioLibraryLayer"));
        if (audioLibrary)
        {
            audioLibrary->setAudioFiles(serializer.audioFiles());
        }
    }

}