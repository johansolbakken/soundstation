#pragma once

#include "core/layer.h"

#include "audio/audiobuffer.h"

namespace SoundStation
{
    class FileReaderWriterLayer : public Layer
    {
    public:
        FileReaderWriterLayer();
        ~FileReaderWriterLayer() override = default;

        void onUIRender() override;

        void show() { m_open = true; }

        static std::string staticName() { return "FileReaderWriterLayer"; }

    private:
        std::shared_ptr<AudioBuffer> m_buffer;
        char m_filename[1024];
        std::string m_errorString;

        bool m_open = false;
    };
}