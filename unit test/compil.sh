#!/bin/bash

../setup.sh
lib=""
for pparam in "$@"
do
    lib="$pparam $lib"
done
gcc test.c $lib -lud_tensor -o executable
./executable