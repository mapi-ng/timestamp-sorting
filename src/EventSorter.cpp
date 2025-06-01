#include "EventSorter.h"

#include <algorithm>
#include <execution>
#include <ranges>

std::vector<Event> EventSorter::queueForSorting(Frame& frame) {
  m_previous_events.insert(m_previous_events.end(), frame.m_events.begin(),
                           frame.m_events.end());
  // Sort all events ascending by timestamp
  std::sort(std::execution::par, m_previous_events.begin(),
            m_previous_events.end(), [](const Event& a, const Event& b) {
              return a.m_timestamp < b.m_timestamp;
            });

  const int64_t max_ts_with_padding =
      static_cast<int64_t>(m_previous_events.back().m_timestamp) -
      static_cast<int64_t>(m_max_delay);
  if (max_ts_with_padding < 0) {
    return {};
  }

  // Get iterator to split range with 100ns margin from the top of the range
  auto it = std::ranges::lower_bound(m_previous_events, max_ts_with_padding,
                                     std::less<>{}, &Event::m_timestamp);
  // Get sorted part without 100 ns margin
  std::vector<Event> sorted = {m_previous_events.begin(), it};

  // Keep last 100 ns of events.
  m_previous_events = {it, m_previous_events.end()};

  // Return sorted part that won't interfere with next frame
  return sorted;
}

std::vector<Event> EventSorter::flush() { return std::move(m_previous_events); }
