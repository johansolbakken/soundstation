#pragma once

#include "core/layer.h"

namespace SoundStation
{
    class ProjectLayer : public Layer
    {
    public:
        ProjectLayer();
        ~ProjectLayer() = default;

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep t) override;
        void onUIRender() override;

        std::string projectName() const { return m_projectName; }
        uint32_t sampleRate() const { return m_sampleRate; }

    private:
        char m_projectName[1024] = "Untitled";
        uint32_t m_sampleRate = 44100;
    };
}