#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <limits>

#include "scan.hxx"
#include "scanner.hxx"

int
main(int nargs, char* args[]) {
  using namespace boost;
  namespace prop = program_options;
  prop::options_description desc{};
  desc.add_options()
      ("tcp,t", "Сканирование TCP")
      ("udp,u", "Сканирование UDP")(

      "begin,b",
      prop::value<std::uint16_t>()->default_value(1u),
      "Порт, с которого начать сканирование")

      ("end,e",
      prop::value<std::uint16_t>()->default_value(
        std::numeric_limits<std::uint16_t>::max()),
      "Порт, которым завершить сканирование")
      
      ("address,a",
      prop::value<std::string>()->default_value("127.0.0.1"),
      "Адрес хоста");

  prop::variables_map argmap{};

  try {
    prop::store(parse_command_line(nargs, args, desc), argmap);
  } catch (std::exception& exc) {
    std::cout << desc << '\n';
    return 1;
  }

  if (!argmap.count("tcp") && !argmap.count("udp")) {
    std::cout << desc << '\n';
    return 1;
  }

  if (!argmap.count("address")) {
    std::cout << desc << '\n';
    return 1;
  }

  std::uint16_t range_begin_port{argmap["begin"].as<std::uint16_t>()};
  std::uint16_t range_end_port{argmap["end"].as<std::uint16_t>()};
  std::string address{argmap["address"].as<std::string>()};

  if (range_begin_port > range_end_port) {
    std::cout << "Порт начала не должен превосходить порт конца" << '\n';
    return 1;
  }

  bool tcp{1u <= argmap.count("tcp")};
  bool udp{1u <= argmap.count("udp")};

  portscan::scan scan{
    .udp = udp,
    .tcp = tcp,
    .port_range{range_begin_port, range_end_port},
    .address{address}
  };

  std::cout << scan << '\n';

  portscan::scanner scanner{scan};
  auto scan_result{scanner()};

  if (udp) {
    for (std::uint16_t port : scan_result.first) {
      std::cout << "UDP " << port << '\n';
    }
  }

  if (tcp) {
    for (std::uint16_t port : scan_result.second) {
      std::cout << "TCP " << port << '\n';
    }
  }

}
