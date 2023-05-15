#include <forward_list>
#include <cstdint>
#include <ostream>
#include "scanres.hxx"

using portlist = std::forward_list<std::uint16_t>;

portscan::scanres::scanres(const portlist& udp, const portlist& tcp)
    : udp_{udp}, tcp_{tcp} {}

portlist portscan::scanres::udp() const {
  return udp_;
}

portlist portscan::scanres::tcp() const {
  return tcp_;
}

std::ostream& portscan::operator<<(std::ostream& os, const portscan::scanres& scr) {
  for (auto port : scr.udp()) {
    os << "UDP " << port << '\n';
  }

  for (auto port : scr.tcp()) {
    os << "TCP " << port << '\n';
  }

  return os;
}