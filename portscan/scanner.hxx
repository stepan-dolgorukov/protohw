#pragma once
#include "scan.hxx"
#include <boost/system/detail/error_category.hpp>
#include <boost/system/detail/error_code.hpp>
#include <forward_list>
#include "scanres.hxx"

namespace portscan {
  class scanner;
};

class portscan::scanner {
  private:
  portscan::scan scan_;

  public:
  scanner(const portscan::scan& scan) : scan_{scan} {
  };

  portscan::scanres operator()();

  private:
  std::forward_list<std::uint16_t> udp_scan(
    const std::string& addr,
    std::pair<std::uint16_t, std::uint16_t> port_range);

  std::forward_list<std::uint16_t> tcp_scan(
    const std::string& addr,
    std::pair<std::uint16_t, std::uint16_t> port_range);

  bool udp_port_opened(
    const std::string& addr,
    std::uint16_t port);

  bool tcp_port_opened(
    const std::string& addr,
    std::uint16_t port);
};