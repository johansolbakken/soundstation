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

        m_window = std::make_unique<Window>(spec);
        m_window->show();

        Renderer::init();

        {
            float aspectRatio = float(spec.width) / float(spec.height);
            float scale = 0.4;
            glm::mat4 proj = glm::mat4(1.0f);
            proj = glm::translate(proj, glm::vec3(0.0f, 0.3f, 0.0f));
            proj = glm::scale(proj, glm::vec3(scale, scale, 1.0f));
            proj = proj * glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

            auto ogre = Texture::create();
            ogre->load("assets/images/ogre.png");
            ogre->bind();

            auto shader = Shader::create("assets/shaders/texture.vert", "assets/shaders/texture.frag");
            shader->bind();
            shader->setInt("tex", 0);
            shader->setMat4("projection", proj);
        
            audioDevice->setAudioBuffer(audioFiles[rand() % audioFiles.size()]->audioBuffer());

            auto startTime = Time::systemTimeSeconds();
            while (Time::systemTimeSeconds() - startTime < 20.0f)
            {
                RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
                RenderCommand::clear();

                RenderCommand::drawArrays(6);

                m_window->onUpdate();
            }
        }

        Renderer::shutdown();
    }
}