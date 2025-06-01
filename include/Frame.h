#pragma once

#include <cstdint>
#include <vector>

#include "Event.h"

struct Frame {
  uint32_t m_events_number;
  uint32_t m_id;
  std::vector<Event> m_events;
};