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
}