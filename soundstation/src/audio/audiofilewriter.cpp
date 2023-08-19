#include "audiofilewriter.h"

#include <fstream>

#include <sndfile.h>

#include "core/log.h"
#include "core/assert.h"

namespace SoundStation
{
    void AudioFileWriter::write(const std::string &filename, const std::shared_ptr<AudioBuffer> &buffer, AudioFileFormat format)
    {
        SS_LOG_INFO(fmt::format("Writing to {}", filename));

        SF_INFO info;
        info.channels = buffer->channels();
        info.samplerate = buffer->sampleRate();
        info.format = static_cast<int>(format) | SF_FORMAT_FLOAT;

        SNDFILE* file = sf_open(filename.c_str(), SFM_WRITE, &info);
        SS_ASSERT(file, "Failed to open file");

        sf_count_t count = sf_write_float(file, buffer->data(), buffer->size());
        SS_ASSERT(count == buffer->size(), "Failed to write to file");

        sf_close(file);
    }
}