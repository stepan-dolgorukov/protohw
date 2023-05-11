#include "scanner.hxx"
#include <asm-generic/socket.h>
#include <forward_list>
#include <iostream>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>

std::pair<std::forward_list<std::uint16_t>, std::forward_list<std::uint16_t>>
portscan::scanner::operator()() {

  std::pair<std::forward_list<std::uint16_t>, std::forward_list<std::uint16_t>> result{};

  if (scan_.udp) {
    result.first = udp_scan(scan_.address, scan_.port_range);
  }

  if (scan_.tcp) {
    result.second = tcp_scan(scan_.address, scan_.port_range);
  }

  return result;
}

std::forward_list<std::uint16_t> portscan::scanner::udp_scan(
  const std::string& address,
  std::pair<std::uint16_t, std::uint16_t> port_range) {

    std::forward_list<std::uint16_t> opened_ports{};
    int sock{-1};

    sockaddr_in addr{
      .sin_family = AF_INET,
    };

    if (0 >= inet_pton(AF_INET, address.c_str(), &addr.sin_addr)) {
      return {};
    }

    char s[128u]{};

    for (std::uint16_t port{port_range.first}; 0u != port && port <= port_range.second; ++port) {
      sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

      if (sock == -1) {
        continue;
      }

      addr.sin_port = htons(port);

      ssize_t nbytes{sendto(
        sock,
        "portscan",
        9u,
        0,
        (sockaddr*)&addr,
        sizeof addr
      )};

      if(0 > nbytes){
        close(sock);
        continue;
      }

      struct timeval tv{.tv_sec = 1, .tv_usec = 500};
      setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);

      socklen_t socklen{sizeof addr};
      if (0 <= recvfrom(sock, (void*)s, 128u, 0, (sockaddr*)&addr, &socklen)) {
        opened_ports.push_front(port);
      }

      close(sock);
    }

    return opened_ports;
  }

std::forward_list<std::uint16_t> portscan::scanner::tcp_scan(
  const std::string& address,
  std::pair<std::uint16_t, std::uint16_t> port_range) {

    std::forward_list<std::uint16_t> opened_ports{};
    int sock{-1};

    sockaddr_in addr{
      .sin_family = AF_INET,
    };

    if (0 >= inet_pton(AF_INET, address.c_str(), &addr.sin_addr)) {
      return {};
    }

    for (std::uint16_t port{port_range.first}; 0u != port && port <= port_range.second; ++port) {
      sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

      if (-1 == sock) {
        continue;
      }

      addr.sin_port = htons(port);

      int timeout{2000};
      setsockopt(sock, SOL_TCP, TCP_USER_TIMEOUT, (char*) &timeout, sizeof (timeout));

      if (0 == connect(sock, (struct sockaddr*)&addr, sizeof(addr))) {
        opened_ports.push_front(port);
      }

      close(sock);
    }

    return opened_ports;
  }