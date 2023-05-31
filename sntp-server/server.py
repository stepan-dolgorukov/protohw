#!/usr/bin/env python3

import socket
from reply import timestamp_from_request, make_reply_packet

def run_server(port):
    UDP_IP = ""
    UDP_PORT = port

    sock = socket.socket(socket.AF_INET,
                         socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))

    while True:
        data, sender = sock.recvfrom(128)
        responce = make_reply_packet(data, 10)
        sock.sendto(responce, sender)

if __name__ == '__main__':
    run_server(123)