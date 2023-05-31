#!/usr/bin/env python3

from timestamp import current_timestamp
from struct import pack

def make_request_packet():
    # 11.. .... Leap Indicator, значение: 3
    # ..10 0... Version Number, значение: 4
    # .... .011 Mode, значение: 3
    flags = pack("!B", 0xe3)

    peer_clock_stratum = pack("!B", 0)
    peer_polling_interval = pack("!B", 3)

    # 0xfa = 250
    # 0.015625
    peer_clock_precision = pack("!B", 0xfa)

    root_delay = pack("!I", 0x01_00_00)
    root_dispersion = pack("!I", 0x01_00_00)

    reference_id = pack("!I", 0)

    reference_timestamp = pack("!Q", 0)
    origin_timestamp = pack("!Q", 0)
    receive_timestamp = pack("!Q", 0)
    transmit_timestamp = pack("!Ixxxx", current_timestamp())

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