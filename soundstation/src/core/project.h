#pragma once

namespace SoundStation
{
    class Project
    {
    public:
        Project() = default;
        ~Project() = default;

        void setName(const std::string &name) { m_name = name; }
        const std::string &name() const { return m_name; }

        void setPath(const std::string &path) { m_path = path; }
        const std::string &path() const { return m_path; }

        void setSampleRate(uint32_t sampleRate) { m_sampleRate = sampleRate; }
        uint32_t sampleRate() const { return m_sampleRate; }

        void setBufferSize(uint32_t bufferSize) { m_bufferSize = bufferSize; }
        uint32_t bufferSize() const { return m_bufferSize; }

    private:
        std::string m_name = "Untitled";
        std::string m_path = "";
        uint32_t m_sampleRate = 48000;
        uint32_t m_bufferSize = 1024;
    };
}