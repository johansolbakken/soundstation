#include "audiofilewriter.h"

#include <fstream>

#include "core/log.h"
#include "core/assert.h"

namespace SoundStation
{
    void writeAif(const std::string& filename, const std::shared_ptr<AudioBuffer>& buffer) {
        // todo(johan): implement
    }

    void AudioFileWriter::write(const std::string &filename, const std::shared_ptr<AudioBuffer> &buffer, AudioFileFormat format)
    {
        switch (format)
        {
        case AudioFileFormat::Aiff:
            writeAif(filename, buffer);
            break;
        
        default:
            SS_ASSERT(false, "Unknown audio file format");
            break;
        }
    }
}