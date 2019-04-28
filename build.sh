#!/usr/bin/env bash
cd scripts
./genver.sh
cd ..
gcc src/main.c src/star.c $1 -Wall -lm -o pssg