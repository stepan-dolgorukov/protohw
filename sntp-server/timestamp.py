#!/usr/bin/env python3

from datetime import datetime, timezone

def timestamp(date):
    since = date - datetime(1900, 1, 1, 0, 0, 0)
    return int(since.total_seconds())

def current_timestamp():
    return timestamp(datetime.utcnow())

if __name__ == '__main__':
    print(hex(current_timestamp()))