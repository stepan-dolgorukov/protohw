#pragma once
#include <string>
#include <cstdint>
#include <ostream>

namespace portscan {
  struct scan;
};

struct portscan::scan {
  bool udp, tcp;
  std::pair<std::uint16_t, std::uint16_t> port_range;
  std::string address;

  friend std::ostream& operator<<(std::ostream& os, const portscan::scan& sc);
};