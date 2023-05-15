#include "scanner.hxx"
#include <asm-generic/socket.h>
#include <forward_list>
#include <iostream>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>

portscan::scanres portscan::scanner::operator()() {

  std::forward_list<std::uint16_t> udp{}, tcp{};

  if (scan_.udp) {
    udp = udp_scan(scan_.address, scan_.port_range);
  }

  if (scan_.tcp) {
    tcp = tcp_scan(scan_.address, scan_.port_range);
  }

  return {udp, tcp};
}

std::forward_list<std::uint16_t> portscan::scanner::udp_scan(
  const std::string& address,
  std::pair<std::uint16_t, std::uint16_t> port_range) {

    std::forward_list<std::uint16_t> opened_ports{};

    for (std::uint16_t port{port_range.first}; 0u != port && port <= port_range.second; ++port) {
      if (udp_port_opened(address, port)) {
        opened_ports.push_front(port);
      }
    }

    return opened_ports;
  }

bool portscan::scanner::udp_port_opened(
  const std::string& address,
  std::uint16_t port) {

  sockaddr_in addr{
    .sin_family = AF_INET,
  };

  if (0 >= inet_pton(AF_INET, address.c_str(), &addr.sin_addr)) {
    return false;
  }

  char received[128u]{};
  char msg[]{"portscan"};

  int sock{socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)};

  if (-1 == sock) {
    return false;
  }

  addr.sin_port = htons(port);

  ssize_t nbytes{sendto(
    sock,
    msg,
    sizeof msg,
    0,
    (sockaddr*)&addr,
    sizeof addr
  )};

  if(0 > nbytes){
    close(sock);
    return false;
  }

  struct timeval tv{.tv_sec = 1, .tv_usec = 500};
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);

  socklen_t socklen{sizeof addr};
  if (0 > recvfrom(sock, (void*)received, sizeof received, 0, (sockaddr*)&addr, &socklen)) {
    close(sock);
    return false;
  }

  return true;
} 

std::forward_list<std::uint16_t> portscan::scanner::tcp_scan(
  const std::string& address,
  std::pair<std::uint16_t, std::uint16_t> port_range) {

  std::forward_list<std::uint16_t> opened_ports{};

  for (std::uint16_t port{port_range.first}; 0u != port && port <= port_range.second; ++port) {
    if (tcp_port_opened(address, port)) {
      opened_ports.push_front(port);
    }
  }

  return opened_ports;
}

bool portscan::scanner::tcp_port_opened(
  const std::string& address,
  std::uint16_t port) {

  sockaddr_in addr{
    .sin_family = AF_INET,
  };

  if (0 >= inet_pton(AF_INET, address.c_str(), &addr.sin_addr)) {
    return false;
  }

  int sock{socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)};

  if (-1 == sock) {
    return false;
  }

  addr.sin_port = htons(port);

  int timeout{2000};
  setsockopt(sock, SOL_TCP, TCP_USER_TIMEOUT, (char*) &timeout, sizeof (timeout));

  if (0 != connect(sock, (struct sockaddr*)&addr, sizeof(addr))) {
    close(sock);
    return false;
  }

  return true;
}