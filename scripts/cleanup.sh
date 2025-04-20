#!/bin/bash

set -eu

target=${1:-problems}

cleanup() {
    mv main.cpp "${1}"
    cp base.cpp main.cpp
    sed -i '' '/atcoder/d' main.cpp
    sed -i '' '/INF/d' main.cpp
    sed -i '' '/\/\//d' main.cpp
    rm -f main
}

if [ "$target" = 'contest' ]; then
    path="./code/contest/${2}"
    [ -d "${path}" ] || mkdir "${path}"
    cleanup "${path}/${3}.cpp"
    exit 0
fi

last_num=$(find ./code/${target} -type f -name '*.cpp' | sed -E 's/.*\/([0-9]+)\.cpp/\1/' | sort -n | tail -1)
new_number=$((10#$last_num+1))
filename=$(printf "%03d" ${new_number})

cleanup "./code/${target}/${filename}.cpp"
