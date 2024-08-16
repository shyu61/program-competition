#!/bin/bash

n=$(find ./code/problems -type f -name 'main*.cpp' | sed -E 's/.*main([0-9]+)\.cpp/\1/' | sort -n | tail -1)
filename=$((n+1))

mv main.cpp ./code/problems/main${filename}.cpp
cp base.cpp main.cpp
rm main
