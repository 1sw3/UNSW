#!/bin/bash

# Play my python3 program against the specified program

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <port> " >&2
    exit 1
fi

./servt -p $1 & sleep 0.1
./lookt -d 7 -p $1 & sleep 0.1
