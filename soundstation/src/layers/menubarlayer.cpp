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
        : Layer("MenuBarLayer")
    {
    }

    void MenuBarLayer::onAttach()
    {
    }

    void MenuBarLayer::onDetach()
    {
    }

    void MenuBarLayer::onUpdate(Timestep t)
    {
    }

    void MenuBarLayer::onUIRender()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "Ctrl+O/Command+O"))
                {
                    auto projectLayer = static_cast<ProjectLayer *>(Application::instance().getLayer("ProjectLayer"));
                    if (projectLayer)
                    {
                        projectLayer->openProject();
                    }
                }

                if (ImGui::MenuItem("Save", "Ctrl+S/Command+S"))
                {
                    auto projectLayer = static_cast<ProjectLayer *>(Application::instance().getLayer("ProjectLayer"));
                    if (projectLayer)
                    {
                        projectLayer->saveProject();
                    }
                }

                if (ImGui::MenuItem("Save As", "Ctrl+Shift+S/Command+Shift+S"))
                {
                    auto projectLayer = static_cast<ProjectLayer *>(Application::instance().getLayer("ProjectLayer"));
                    if (projectLayer)
                    {
                        projectLayer->saveProjectAs();
                    }
                }

                if (ImGui::MenuItem("Project Settings"))
                {
                    auto projectLayer = static_cast<ProjectLayer *>(Application::instance().getLayer("ProjectLayer"));
                    if (projectLayer)
                    {
                        projectLayer->show();
                    }
                }

                if (ImGui::MenuItem("Quit", "Ctrl+Q/Command+Q"))
                {
                    Application::instance().close();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Audio Device Manager"))
                {
                    auto audioDeviceManager = static_cast<AudioDeviceManagerLayer *>(Application::instance().getLayer("AudioDeviceManagerLayer"));
                    if (audioDeviceManager)
                        audioDeviceManager->show();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Tools"))
            {
                if (ImGui::MenuItem("File Reader Writer"))
                {
                    auto fileReaderWriter = static_cast<FileReaderWriterLayer *>(Application::instance().getLayer("FileReaderWriterLayer"));
                    if (fileReaderWriter)
                        fileReaderWriter->show();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

}
