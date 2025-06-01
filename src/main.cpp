#include <format>
#include <fstream>
#include <iostream>

#include "EventSorter.h"
#include "FrameLoader.h"

int main(int argc, char* argv[]) {
  std::cout << "Please, provide path to data file: ";
  std::string path;
  std::cin >> path;
  std::erase_if(path, [](char c) { return c == '\''; });
  std::ofstream sorted_file("./sorted_events.tsv");

  FrameLoader loader(path);
  EventSorter sorter;

  sorted_file << "Time\tEnergy\n";
  while (auto frame_opt = loader.nextFrame()) {
    auto events = sorter.queueForSorting(frame_opt.value());
    for (const auto& event : events) {
      sorted_file << std::format("{}\t{}\n", event.m_timestamp, event.m_energy);
    }
  }
  for (const auto& event : sorter.flush()) {
    sorted_file << std::format("{}\t{}\n", event.m_timestamp, event.m_energy);
  }

  return 0;
}