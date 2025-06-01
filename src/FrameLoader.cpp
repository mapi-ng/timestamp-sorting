#include "FrameLoader.h"

FrameLoader::FrameLoader(const std::filesystem::path& path) {
  m_file.open(path, std::ios::binary);
}

std::optional<Frame> FrameLoader::nextFrame() {
  Frame frame;
  if (m_file.read(reinterpret_cast<char*>(&frame.m_events_number),
                  sizeof(uint32_t))) {
    m_file.read(reinterpret_cast<char*>(&frame.m_id), sizeof(uint32_t));

    for (size_t i = 0; i < frame.m_events_number; ++i) {
      uint32_t timestamp;
      uint32_t energy;
      m_file.read(reinterpret_cast<char*>(&timestamp), sizeof(uint32_t));
      m_file.read(reinterpret_cast<char*>(&energy), sizeof(uint32_t));
      frame.m_events.push_back({timestamp, energy});
    }
  } else {
    if (m_file.eof()) {
      return std::nullopt;
    } else {
      throw std::invalid_argument("Error when reading input file");
    }
  }

  return frame;
}
