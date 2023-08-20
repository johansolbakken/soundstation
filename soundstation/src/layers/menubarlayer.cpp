#include "menubarlayer.h"

#include "core/application.h"

#include <imgui.h>

#include "serializer/serializer.h"

#include "layers/audiolibrarylayer.h"
#include "layers/audiodevicemanagerlayer.h"

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
                /*if (ImGui::MenuItem("Open"))
                {
                    Application::get().openFile();
                }
                */

                if (ImGui::MenuItem("Save"))
                {
                    Serializer serializer;

                    auto audioLibrary = static_cast<AudioLibraryLayer *>(Application::instance().getLayer("AudioLibraryLayer"));
                    if (audioLibrary)
                    {
                        serializer.setAudioFiles(audioLibrary->audioFiles());
                    }

                    serializer.serialize("test.soundstation");
                }

                if (ImGui::MenuItem("Quit"))
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
                    {
                        audioDeviceManager->showAudioDeviceManager(true);
                    }
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

}
