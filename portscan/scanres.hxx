#pragma once
#include <forward_list>
#include <cstdint>
#include <ostream>

namespace portscan {
  class scanres;
  enum class proto : std::uint8_t;
};

class portscan::scanres {
  using portlist = std::forward_list<std::uint16_t>;

  private:
  portlist udp_{}, tcp_{};

  public:
  scanres(const portlist& udp, const portlist& tcp);
  portlist udp() const;
  portlist tcp() const;
  friend std::ostream& operator<<(std::ostream& os, const scanres& scr);
};