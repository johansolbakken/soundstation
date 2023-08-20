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
        auto audioDeviceList = AudioDeviceList::create();
        audioDeviceList->onUpdate();
        auto audioDevice = AudioDevice::create(audioDeviceList->defaultOutputDeviceId());

        std::vector<std::shared_ptr<AudioFile>> audioFiles = {
            AudioFile::create("assets/sound/comboplease.mp3"),
            AudioFile::create("assets/sound/informasjones.mp3"),
        };

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
            float aspectRatio = float(m_window->width()) / float(m_window->height());
            float scale = 0.4;
            glm::mat4 imageProj = glm::mat4(1.0f);
            imageProj = glm::translate(imageProj, glm::vec3(0.0f, 0.3f, 0.0f));
            imageProj = glm::scale(imageProj, glm::vec3(scale, scale, 1.0f));
            imageProj = imageProj * glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

            auto ogre = Texture::create();
            ogre->load("assets/images/ogre.png");
            auto shader = Shader::create("assets/shaders/texture.vert", "assets/shaders/texture.frag");

            // audioDevice->setAudioBuffer(audioFiles[rand() % audioFiles.size()]->audioBuffer());

            ImGuiLayer layer;

            auto startTime = Time::systemTimeSeconds();
            while (Time::systemTimeSeconds() - startTime < 3.0f)
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
                ImGui::Text("SoundStation");
                ImGui::Text("Version 0.0.1");
                ImGui::End();

                layer.end();

                m_window->onUpdate();
            }
        }

        Renderer::shutdown();
    }
}