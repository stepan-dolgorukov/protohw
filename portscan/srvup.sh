#!/usr/bin/env bash

./srv.py 7000 tcp &
./srv.py 7001 udp &
./srv.py 7008 tcp &
./srv.py 7005 udp &