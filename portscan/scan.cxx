#include "scan.hxx"

std::ostream& portscan::operator<<(std::ostream& os, const portscan::scan& sc) {
  return os << "Address: " << sc.address << '\n'
    << "UDP: " << std::boolalpha << sc.udp << '\n'
    << "TCP: " << std::boolalpha << sc.tcp << '\n'
    << "Port Range: [" << sc.port_range.first << ':'
    << sc.port_range.second << "]";
}