#!/usr/bin/env python3

from request import make_request_packet
from timestamp import datetime_by_timestamp, current_timestamp
import socket

def time_from_reply(reply: bytes):
    transmit_timestamp = reply[len(reply) - 8:-4]
    timestamp = int.from_bytes(transmit_timestamp, "big")

    return datetime_by_timestamp(timestamp)


UDP_IP = "127.0.0.1"
UDP_PORT = 123
MESSAGE = make_request_packet()

current_ts = current_timestamp()
print(f"Время до запроса: {datetime_by_timestamp(current_ts)}")

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

reply = sock.recv(128)
print(f"Время на сервере: {time_from_reply(reply)}")