#pragma once

#include <string>

#include "audio/audiobuffer.h"

namespace SoundStation
{

    enum class AudioFileFormat : int
    {
        Unknown,
        Wav = 0x010000,
        Aiff = 0x020000,
        Au = 0x030000,
        Raw = 0x040000,
        Paf = 0x050000,
        Svx = 0x060000,
        Nist = 0x070000,
        Voc = 0x080000,
        Ircam = 0x0A0000,
        W64 = 0x0B0000,
        Mat4 = 0x0C0000,
        Mat5 = 0x0D0000,
        Pvf = 0x0E0000,
        Xi = 0x0F0000,
        Htk = 0x100000,
        Sds = 0x110000,
        Avr = 0x120000,
        Wavex = 0x130000,
        Sd2 = 0x160000,
        Flac = 0x170000,
        Caf = 0x180000,
        Wve = 0x190000,
        Ogg = 0x200000,
        Mpc2k = 0x210000,
        Rf64 = 0x220000,
        Mpeg = 0x230000
    };

    class AudioFileWriter
    {
    public:
        static void write(const std::string &filename, const std::shared_ptr<AudioBuffer> &buffer, AudioFileFormat format);
    };
}