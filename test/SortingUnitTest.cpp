#include <gtest/gtest.h>

#include <format>

#include "EventSorter.h"
#include "FrameLoader.h"

TEST(SortingUnitTest, ReadingFramesOk) {
  FrameLoader loader("raw_data.dat");

  size_t total_events_number{0};
  uint32_t min_ts{0};
  uint32_t max_ts{0};
  while (auto frame_opt = loader.nextFrame()) {
    auto frame = frame_opt.value();
    EXPECT_EQ(frame.m_events_number, frame.m_events.size());

    for (const auto &event : frame.m_events) {
      ++total_events_number;
      if (event.m_timestamp < min_ts) {
        min_ts = event.m_timestamp;
      }
      if (event.m_timestamp > max_ts) {
        max_ts = event.m_timestamp;
      }
    }
  }
  EXPECT_EQ(total_events_number, 969);
  EXPECT_EQ(min_ts, 0);
  EXPECT_EQ(max_ts, 10178);
}

TEST(SortingUnitTest, SortThreeFramesOk) {
  std::vector<Event> events_asc{{0, 1},   {31, 3},  {50, 2}, {63, 9},
                                {72, 4},  {73, 2},  {85, 3}, {102, 7},
                                {153, 1}, {231, 4}, {247, 1}};
  Frame frame1{2, 0, {events_asc[0], events_asc[2]}};
  Frame frame2{2, 1, {events_asc[1], events_asc[4]}};
  Frame frame3{3, 2, {events_asc[3], events_asc[5], events_asc[6]}};
  Frame frame4{2, 3, {events_asc[7], events_asc[9]}};
  Frame frame5{2, 4, {events_asc[8], events_asc[10]}};
  std::vector<Frame> frames{frame1, frame2, frame3, frame4, frame5};

  EventSorter sorter;
  std::vector<Event> events_output;
  for (auto &frame : frames) {
    auto events = sorter.queueForSorting(frame);
    events_output.insert(events_output.end(), events.begin(), events.end());
  }
  auto events = sorter.flush();
  events_output.insert(events_output.end(), events.begin(), events.end());

  ASSERT_EQ(events_output.size(), events_asc.size());
  for (size_t i = 0; i < events_output.size(); ++i) {
    EXPECT_EQ(events_output[i].m_timestamp, events_asc[i].m_timestamp);
  }
}
