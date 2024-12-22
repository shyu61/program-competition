#!/bin/bash

target=${1:-problems}

last_num=$(find ./code/${target} -type f -name '*.cpp' | sed -E 's/.*([0-9]*)\.cpp/\1/' | sort -n | tail -1)
new_number=$((10#$last_num+1))
filename=$(printf "%03d" ${new_number})

mv main.cpp ./code/${target}/${filename}.cpp
cp base.cpp main.cpp
rm -f main
