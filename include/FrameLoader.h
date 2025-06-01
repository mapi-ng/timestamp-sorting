#pragma once
#include <filesystem>
#include <fstream>
#include <optional>

#include "Frame.h"

class FrameLoader {
 private:
  std::ifstream m_file;

 public:
  /**
   * @brief Opens binary file from path to read.
   */
  explicit FrameLoader(const std::filesystem::path &path);

  /**
   * @brief Reads consecutive frame from file at each call.
   */
  std::optional<Frame> nextFrame();
};