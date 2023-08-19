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

        SNDFILE *file = sf_open(filename.c_str(), SFM_WRITE, &info);
        SS_ASSERT(file, "Failed to open file");

        sf_count_t count = sf_write_float(file, buffer->data(), buffer->size());
        SS_ASSERT(count == buffer->size(), "Failed to write to file");

        sf_close(file);
    }

    std::shared_ptr<AudioBuffer> AudioFileWriter::read(const std::string &filename)
    {
        SS_LOG_INFO(fmt::format("Reading from {}", filename));

        SF_INFO info;
        SNDFILE *file = sf_open(filename.c_str(), SFM_READ, &info);
        SS_ASSERT(file, "Failed to open file");

        float *data = new float[info.frames * info.channels];
        sf_count_t count = sf_read_float(file, data, info.frames * info.channels);
        SS_ASSERT(count == info.frames * info.channels, "Failed to read from file");

        size_t bufferSize = info.frames * info.channels;
        AudioBufferFormat format = AudioBufferFormat::Float32Bit;
        std::shared_ptr<AudioBuffer> buffer = std::make_shared<AudioBuffer>(data, bufferSize, info.samplerate, format, info.channels);

        sf_close(file);

        return buffer;
    }
}