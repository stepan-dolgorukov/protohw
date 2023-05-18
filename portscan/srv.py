#!/usr/bin/env python3

import socketserver
import sys

class TcpRequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        data = self.request.recv(512).strip()
        print(f"C: {self.client_address}, D: {data}")

        self.request.sendall(data)

class UdpRequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        data = self.request[0].strip()
        socket = self.request[1]

        print(f"C: {self.client_address}, D: {data}")

        socket.sendto(data, self.client_address)

if __name__ == "__main__":
    host = "localhost"
    port = int(sys.argv[1])
    proto = sys.argv[2].lower()

    print(proto, port)

    if proto == 'tcp':
        with socketserver.TCPServer((host, port), TcpRequestHandler) as server:
            server.serve_forever()

    if proto == 'udp':
        with socketserver.UDPServer((host, port), UdpRequestHandler) as server:
            server.serve_forever()