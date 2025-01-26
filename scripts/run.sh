#!/bin/bash

g++-14 -std=c++20 -I . -g -o main main.cpp

awk 'BEGIN {RS="\n\n"} {f="chunk" NR ".txt"; print > f}' in.txt

if [ $# -eq 1 ]; then
    ./main < "chunk$1.txt"
else
    for chunk in chunk*.txt; do
        ./main < "$chunk"
        echo
    done
fi

rm -r chunk*.txt main
