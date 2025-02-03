#!/bin/bash

set -eu

target=${1:-problems}

if [ $target = 'contest' ]; then
    con=${2}
    [ ! -d ./code/contest/${con} ] && mkdir ./code/contest/${con}
    mv main.cpp ./code/contest/${con}/${3}.cpp
    cp base.cpp main.cpp
    sed -i '' '/atcoder/d' main.cpp
    sed -i '' '/INF/d' main.cpp
    rm -f main
    exit 0
fi

last_num=$(find ./code/${target} -type f -name '*.cpp' | sed -E 's/.*\/([0-9]+)\.cpp/\1/' | sort -n | tail -1)
new_number=$((10#$last_num+1))
filename=$(printf "%03d" ${new_number})

mv main.cpp ./code/${target}/${filename}.cpp
cp base.cpp main.cpp
sed -i '' '/atcoder/d' main.cpp
sed -i '' '/INF/d' main.cpp
rm -f main
