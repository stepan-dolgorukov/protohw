#pragma once
#include "scan.hxx"
#include <boost/system/detail/error_category.hpp>
#include <boost/system/detail/error_code.hpp>
#include <forward_list>

namespace portscan {
  class scanner;
};

class portscan::scanner {
  private:
  portscan::scan scan_;

  public:
  scanner(const portscan::scan& scan) : scan_{scan} {
  };

  std::pair<std::forward_list<std::uint16_t>, std::forward_list<std::uint16_t>>
  operator()();

  private:
  std::forward_list<std::uint16_t> udp_scan(
    const std::string& addr,
    std::pair<std::uint16_t, std::uint16_t> port_range);

  std::forward_list<std::uint16_t> tcp_scan(
    const std::string& addr,
    std::pair<std::uint16_t, std::uint16_t> port_range);
};