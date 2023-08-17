#include "application.h"

#include "core/log.h"

namespace SoundStation
{
    class TestLayer : public Layer
    {
    public:
        TestLayer()
            : Layer("Test")
        {
        }

        void onUpdate() override
        {
            SS_LOG_INFO("TestLayer::onUpdate");
        }

        void onAttach() override
        {
            SS_LOG_INFO("TestLayer::onAttach");
        }

        void onDetach() override
        {
            SS_LOG_INFO("TestLayer::onDetach");
        }
    };

    Application::Application()
    {
        auto l = new TestLayer();
        m_layerStack.pushLayer(l);

        SS_LOG_INFO("SoundStation is awake!");

        l->onAttach();
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        while (m_running) {
            for (Layer *layer : m_layerStack)
            {
                layer->onUpdate();
            }
        }
    }
}