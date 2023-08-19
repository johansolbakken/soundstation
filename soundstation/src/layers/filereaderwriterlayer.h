#pragma once

#include "core/layer.h"

#include "audio/audiobuffer.h"

#include <string>

namespace SoundStation
{

    class FileReaderWriterLayer : public Layer
    {
    public:
        FileReaderWriterLayer();
        ~FileReaderWriterLayer() override = default;

        void onAttach() override;
        void onDetach() override;
        void onUpdate(Timestep t) override;
        void onUIRender() override;

    private:
        std::shared_ptr<AudioBuffer> m_buffer;
        char m_filename[1024];
        std::string m_errorString;
    };

}