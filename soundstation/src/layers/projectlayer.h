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

        uint32_t m_sampleRate = 44100;
        bool m_sampleRateChanged = false;

        Project m_project;
        bool m_open = false;
    };
}