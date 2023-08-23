#pragma once

#include "core/layer.h"
#include "core/project.h"

namespace SoundStation
{
    class ProjectLayer : public Layer
    {
    public:
        ProjectLayer();
        ~ProjectLayer() = default;

        void onUIRender() override;

        const Project &project() const { return m_project; }

        void newProject();
        void saveProject();
        void saveProjectAs();
        void openProject();

        void show() { m_open = true; }

        static std::string staticName() { return "ProjectLayer"; }

    private:
        char m_projectName[1024] = "Untitled";
        bool m_projectNameChanged = false;

        uint32_t m_sampleRate = 48000;
        bool m_sampleRateChanged = false;

        uint32_t m_bufferSize = 1024;
        bool m_bufferSizeChanged = false;

        Project m_project;
        bool m_open = false;
    };
}