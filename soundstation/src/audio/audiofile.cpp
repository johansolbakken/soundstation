#include "audiofile.h"

#include "audiofilewriter.h"

namespace SoundStation {
    AudioFile::AudioFile(const std::string &filename)
        : m_filename(filename)
    {
        m_buffer = AudioFileWriter::read(filename);
    }

    AudioFile::~AudioFile()
    {
    }

    std::shared_ptr<AudioFile> AudioFile::create(const std::string &filename) {
        return std::make_shared<AudioFile>(filename);
    }
}