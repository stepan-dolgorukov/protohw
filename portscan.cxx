#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>

int
main(int nargs, char* args[]) {
  using namespace boost;
  namespace prop = program_options;
  prop::options_description desc{};
  desc.add_options()("tcp,t", "Сканирование TCP")("udp,u", "Сканирование UDP")(
      "begin,b", prop::value<std::uint16_t>()->default_value(1u),
      "Порт, с которого начать сканирование")(
      "end,e", prop::value<std::uint16_t>()->default_value(65535u),
      "Порт, которым завершить сканирование");

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

  std::cout << argmap["begin"].as<std::uint16_t>() << ' '
            << argmap["end"].as<std::uint16_t>() << '\n';
}
