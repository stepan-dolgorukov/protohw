#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <limits>

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

  if (!argmap.count("begin") || !argmap.count("end")) {
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

  std::cout << range_begin_port << ' '
            << range_end_port << '\n';

  std::cout << address << '\n';
}
