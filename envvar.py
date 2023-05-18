#!/usr/bin/env python3

import os

if __name__ == '__main__':
    for variable, value in os.environ.items():
        print(variable, value)
