#!/usr/bin/env python3

import socket
import argparse
import sys
from reply import timestamp_from_request, make_reply_packet
from multiprocessing.pool import ThreadPool

def serve(sock, data, sender, delay):
    responce = make_reply_packet(data, delay)
    sock.sendto(responce, sender)


def run_server(port, delay):
    UDP_IP = ""
    UDP_PORT = port

    sock = socket.socket(socket.AF_INET,
                         socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))

    print(
        f"Сервер успешно запущен. Порт: {args.port}, смещение-обманка: {args.delay} сек.")

    with ThreadPool() as pool:
        while True:
            data, sender = sock.recvfrom(128)
            pool.apply_async(serve, args=(sock, data, sender, delay))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--port",
        "-p",
        type=int,
        default=55123,
        help="Порт, который будет слушать сервер")

    parser.add_argument(
        "--delay",
        "-d",
        type=int,
        default=5,
        help="Смещение-обманка")

    args = parser.parse_args()

    if args.port is None:
        print("Не указан порт.", file=sys.stderr)
        exit(1)

    if args.delay is None:
        print("Не указано смещение.", file=sys.stderr)
        exit(1)

    try:
        run_server(args.port, args.delay)
    except PermissionError:
        print(
            f"Недостаточно прав для запуска сервера на {args.port} порту.",
            file=sys.stderr)

    except OverflowError as exc:
        print(f"Недопустимое значение порта.", file=sys.stderr)

    except KeyboardInterrupt:
        print("Завершение работы.")
