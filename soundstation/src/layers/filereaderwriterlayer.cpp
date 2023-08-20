#include "filereaderwriterlayer.h"

#include <imgui.h>

#include "audio/audiofilewriter.h"

#include <filesystem>

namespace SoundStation
{
    FileReaderWriterLayer::FileReaderWriterLayer()
        : Layer("FileReaderWriterLayer")
    {
        memset(m_filename, 0, 1024);
    }

    void FileReaderWriterLayer::onAttach()
    {
    }

    void FileReaderWriterLayer::onDetach()
    {
    }

    void FileReaderWriterLayer::onUpdate(Timestep t)
    {
    }

    void FileReaderWriterLayer::onUIRender()
    {
        if (!m_open)
            return;

        ImGui::Begin("FileReaderWriterLayer", &m_open);
        ImGui::InputText("Filename", m_filename, 1024);
        ImGui::Text("Has file: %s", (m_buffer != nullptr) ? "yes" : "no");

        if (ImGui::Button("Read"))
        {
            if (!std::filesystem::exists(m_filename))
            {
                m_errorString = "File does not exist";
            }
            else
            {
                m_buffer = AudioFileWriter::read(m_filename);
                m_errorString = "";
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Write"))
        {
            if (m_buffer == nullptr)
            {
                m_errorString = "No buffer to write";
            }
            else
            {
                AudioFileWriter::write(m_filename, m_buffer, AudioFileFormat::Aiff);
                m_errorString = "";
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Clear"))
        {
            m_buffer = nullptr;
            m_errorString = "";
        }

        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", m_errorString.c_str());

        ImGui::End();
    }
}