#!/usr/bin/bash
# created by: Evan Hutomo 7/1/2023

## DEFINE
BUILDPATH="$(pwd)/build"
EXENAME="./my_app"

## FUNCTION
usage() {
    echo "Usage: $0 <option>"
    echo "    $0 -c : clean project"
    echo "    $0 -r : run executable"    
    echo "    $0 -a : autobuild and run"        
    exit 1
}

if [ "$1" = "-c" ]; then
    echo "Clean $BUILDPATH"
    rm -rf "$BUILDPATH"
elif [ "$1" = "-r" ]; then
    echo "Run $BUILDPATH"
    cd "$BUILDPATH" && "$EXENAME"    
elif [ "$1" = "-a" ]; then
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
else
    if [ $# -ne 1 ]; then
        usage
    fi
fi

