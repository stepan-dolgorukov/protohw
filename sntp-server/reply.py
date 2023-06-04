#!/usr/bin/env python3

from struct import pack, unpack
from timestamp import current_timestamp


def timestamp_from_request(packet: bytes):
    # Последние 8 байтов пакета
    transmit_timestamp = packet[len(packet) - 8:]
    return transmit_timestamp


def timestamp_with_offset(timestamp: bytes, offset: int):
    timestamp = int.from_bytes(timestamp, byteorder="big")
    offset_seconds = offset * (2**32)

    timestamp += offset_seconds
    return timestamp


def make_reply_packet(request_packet: bytes, offset: int):

    # 00.. .... Leap Indicator: normal, значение: 0
    # ..10 0... Номер версии: NTPv4, значене: 4
    # .... .100 Режим: сервер, значение: 4
    flags = pack("!B", 0x24)

    peer_clock_stratum = pack("!B", 0x1)
    peer_polling_interval = pack("!B", 0x0)
    peer_clock_precision = pack("!B", 0x0)

    root_delay = pack("!I", 0x0)
    root_dispersion = pack("!I", 0x0)
    reference_id = pack("!I", 0x0)

    request_timestamp = timestamp_from_request(request_packet)
    modified_timestamp = timestamp_with_offset(request_timestamp, offset)

    reference_timestamp = pack("!Q", modified_timestamp)
    origin_timestamp = timestamp_from_request(request_packet)
    receive_timestamp = pack("!Q", modified_timestamp)
    transmit_timestamp = pack("!Q", modified_timestamp)

    packet = flags + \
        peer_clock_stratum + \
        peer_polling_interval + \
        peer_clock_precision + \
        root_delay + \
        root_dispersion + \
        reference_id + \
        reference_timestamp + \
        origin_timestamp + \
        receive_timestamp + \
        transmit_timestamp

    return packet
