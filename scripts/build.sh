#!/usr/bin/env sh
cd ..
gcc src/main.c src/star.c -Wall -lm -lgsl -lgslcblas -o pssg