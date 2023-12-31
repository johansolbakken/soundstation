#include "pch.h"
#include "projectlayer.h"

#include "core/application.h"
#include "core/platform.h"

#include "serializer/serializer.h"

#include "layers/audiolibrarylayer.h"
#include "layers/playerlayer.h"

#include <imgui.h>

namespace SoundStation
{

    ProjectLayer::ProjectLayer()
        : Layer(staticName())
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

        if (ImGui::InputInt("Buffer Size", (int *)&m_bufferSize, 1, 1024))
        {
            m_bufferSizeChanged = true;
        }
        else if (m_bufferSizeChanged && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
        {
            m_bufferSizeChanged = false;
            m_project.setBufferSize(m_bufferSize);
        }

        ImGui::End();
    }

    void ProjectLayer::newProject()
    {
        m_project = Project();
        memset(m_projectName, 0, sizeof(m_projectName));
        strcpy(m_projectName, m_project.name().c_str());

        m_sampleRate = m_project.sampleRate();

        if (auto audioLibrary = Application::instance().getLayer<AudioLibraryLayer>())
            audioLibrary->clearAudioFiles();

        if (auto playerLayer = Application::instance().getLayer<PlayerLayer>())
            playerLayer->clearAudioFile();
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

        if (auto audioLibrary = Application::instance().getLayer<AudioLibraryLayer>())
            serializer.setAudioFiles(audioLibrary->audioFiles());

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

        if (auto audioLibrary = Application::getLayer<AudioLibraryLayer>())
            audioLibrary->setAudioFiles(serializer.audioFiles());
    }
}