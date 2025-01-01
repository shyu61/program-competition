#!/bin/bash

g++-14 -std=c++20 -I . -g -o main main.cpp

awk 'BEGIN {RS="\n\n"} {f="chunk" NR ".txt"; print > f}' in.txt

for chunk in chunk*.txt; do
    cat "$chunk" | ./main
done

rm -r chunk*.txt
