#include "menubarlayer.h"

#include "core/application.h"

#include <imgui.h>

#include "layers/audiolibrarylayer.h"
#include "layers/audiodevicemanagerlayer.h"
#include "layers/filereaderwriterlayer.h"
#include "layers/projectlayer.h"

namespace SoundStation
{
    MenuBarLayer::MenuBarLayer()
        : Layer(staticName())
    {
    }

    void MenuBarLayer::onUIRender()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Cmd+N"))
                {
                    if (auto projectLayer = Application::getLayer<ProjectLayer>())
                        projectLayer->newProject();
                }

                if (ImGui::MenuItem("Open", "Cmd+O"))
                {
                    if (auto projectLayer = Application::getLayer<ProjectLayer>())
                        projectLayer->openProject();
                }

                if (ImGui::MenuItem("Save", "Cmd+S"))
                {
                    if (auto projectLayer = Application::getLayer<ProjectLayer>())
                        projectLayer->saveProject();
                }

                if (ImGui::MenuItem("Save As", "Cmd+Shift+S"))
                {
                    if (auto projectLayer = Application::getLayer<ProjectLayer>())
                        projectLayer->saveProjectAs();
                }

                if (ImGui::MenuItem("Project Settings"))
                {
                    if (auto projectLayer = Application::getLayer<ProjectLayer>())
                        projectLayer->show();
                }

                if (ImGui::MenuItem("Quit", "Cmd+Q"))
                {
                    Application::instance().close();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Audio Device Manager"))
                {
                    if (auto audioDeviceManager = Application::getLayer<AudioDeviceManagerLayer>())
                        audioDeviceManager->show();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Tools"))
            {
                if (ImGui::MenuItem("File Reader Writer"))
                {
                    if (auto fileReaderWriter = Application::getLayer<FileReaderWriterLayer>())
                        fileReaderWriter->show();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }
}
