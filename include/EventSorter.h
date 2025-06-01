#pragma once

#include "Frame.h"

class EventSorter {
 private:
  static constexpr uint32_t m_max_delay{100};
  std::vector<Event> m_previous_events;

 public:
  /**
   * @description
   * 1. Extracts events from frame.
   * 2. Adds events to residual events from previous call.
   * 3. Sorts events and returns oldest, without the last 100ns of events.
   * 4. Last 100ns of events remains in the object for the future call.
   */
  std::vector<Event> queueForSorting(Frame &frame);

  /**
   * @description
   * Returns sorted residual events and removes them from the object.
   */
  std::vector<Event> flush();
};