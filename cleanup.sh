#!/bin/bash

target=${1:-problems}

n=$(find ./code/${target} -type f -name 'main*.cpp' | sed -E 's/.*main([0-9]+)\.cpp/\1/' | sort -n | tail -1)
filename=$((n+1))

mv main.cpp ./code/${target}/main${filename}.cpp
cp base.cpp main.cpp
rm -f main
