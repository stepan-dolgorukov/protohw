#!/usr/bin/env python3

import os
import re

def query_string() -> str:
    varname: str = "QUERY_STRING"

    if (qs := os.getenv(varname)) is None:
        raise ValueError(f"Переменная среды «{varname}» не задана")

    return qs

def parse(qs: str) -> dict[str, str]:
    kv_storage = dict()

    if not qs:
        return kv_storage

    for pair in (kv_pairs := qs.split('&')):
        if not (re.fullmatch(".+=.+", pair)):
            continue

        key, value = pair.split('=')
        kv_storage[key] = value

    return kv_storage

if __name__ == '__main__':
    qs = query_string()
    kvs = parse(qs)

    print(kvs)