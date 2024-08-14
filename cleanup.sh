#!/bin/bash

n=$(find ./old -type f -name 'main*.cpp' | sed -E 's/.*main([0-9]+)\.cpp/\1/' | sort -n | tail -1)
filename=$((n+1))

mv main.cpp ./old/main${filename}.cpp
cp base.cpp main.cpp
rm main
