#!/usr/bin/bash
# created by: Evan Hutomo 7/1/2023

## DEFINE
BUILDPATH="$(pwd)/build"

## FUNCTION
usage() {
    echo "Usage: $0 <option>"
    echo "ex: $0 -b : build project"
    echo "    $0 -c : clean project"
    echo "    $0 -a : autobuild and run"        
    exit 1
}

if [ "$1" = "-b" ]; then
    echo "Build $BUILDPATH"
    cd "$BUILDPATH" && cmake --build $BUILDPATH --config Debug --target all -j4         
elif [ "$1" = "-c" ]; then
    echo "Clean $BUILDPATH"
    cd "$BUILDPATH" && make clean
elif [ "$1" = "-a" ]; then
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
else
    if [ $# -ne 1 ]; then
        usage
    fi
fi

