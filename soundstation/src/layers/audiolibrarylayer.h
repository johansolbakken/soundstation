#pragma once

#include "core/layer.h"

#include "audio/audiofile.h"

#include <vector>

namespace SoundStation {
    
        class AudioLibraryLayer : public Layer
        {
        public:
            AudioLibraryLayer();
            ~AudioLibraryLayer() override = default;
    
            void onAttach() override;
            void onDetach() override;
            void onUpdate(Timestep t) override;
            void onUIRender() override;

            std::vector<std::shared_ptr<AudioFile>> audioFiles() const { return m_audioFiles; }
    
        private:
            std::vector<std::shared_ptr<AudioFile>> m_audioFiles;
        };
}