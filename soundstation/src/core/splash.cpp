#include "splash.h"

#include "core/time.h"

#include "renderer/renderer.h"
#include "renderer/texture.h"
#include "renderer/shader.h"

#include "audio/audiodevicelist.h"
#include "audio/audiodevice.h"
#include "audio/audiofile.h"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include <imgui.h>
#include "imgui/imguilayer.h"

#include <stdlib.h>

namespace SoundStation
{
    SplashScreen::SplashScreen()
    {
        WindowSpecification spec;
        spec.title = "Splash Screen";
        spec.width = 300;
        spec.height = 400;
        spec.showMenuBar = false;

        m_window = std::make_shared<Window>(spec);
        m_window->show();
    }

    void SplashScreen::run()
    {

        Renderer::init();

        {
            auto audioDeviceList = AudioDeviceList::create();
            audioDeviceList->onUpdate();
            auto audioDevice = AudioDevice::create(audioDeviceList->defaultOutputDeviceId());

            std::vector<std::string> audioFiles = {
                "assets/sound/comboplease.mp3",
                "assets/sound/informasjones.mp3",
            };

            float aspectRatio = float(m_window->width()) / float(m_window->height());
            float scale = 0.4;
            glm::mat4 imageProj = glm::mat4(1.0f);
            imageProj = glm::translate(imageProj, glm::vec3(0.0f, 0.3f, 0.0f));
            imageProj = glm::scale(imageProj, glm::vec3(scale, scale, 1.0f));
            imageProj = imageProj * glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

            auto ogre = Texture::create();
            ogre->load("assets/images/ogre.png");
            auto shader = Shader::create("assets/shaders/texture.vert", "assets/shaders/texture.frag");

            srand(Time::systemTimeSeconds());
            auto audioFile = AudioFile::create(audioFiles[rand() % audioFiles.size()]);
            auto buffer = audioFile->audioBuffer()->convertSampleRate(audioDevice->sampleRate());
            audioDevice->setAudioBuffer(buffer);
            audioDevice->play();

            // remove path from filename
            std::string filename = audioFile->filename();
            auto lastSlash = filename.find_last_of('/');
            if (lastSlash != std::string::npos)
                filename = filename.substr(lastSlash + 1);

            ImGuiLayer layer;

            bool escapePressed = false;

            while (audioDevice->isPlaying() && !m_window->shouldClose() && !escapePressed)
            {
                RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
                RenderCommand::clear();

                // Draw ogerface
                shader->bind();
                ogre->bind();
                shader->setInt("tex", 0);
                shader->setMat4("projection", imageProj);
                RenderCommand::drawArrays(6);

                float windowX = m_window->x();
                float windowY = m_window->y();

                layer.begin();

                ImGui::SetNextWindowPos(ImVec2(windowX + 20, windowY + 250));

                ImGui::Begin("Splash Screen", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground);

                ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
                ImGui::Text("Sound Station");
                ImGui::PopFont();
                ImGui::Text("Version 0.0.1");
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0));
                ImGui::Text("Playing %s", filename.c_str());
                ImGui::PopStyleColor();

                if (ImGui::IsKeyPressed(ImGuiKey_Escape))
                {
                    escapePressed = true;
                }

                ImGui::End();

                layer.end();

                m_window->onUpdate();
            }

            audioDevice->stop();
        }

        Renderer::shutdown();

        if (m_window->shouldClose())
            exit(0);
    }
}