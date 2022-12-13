#!/bin/bash

clear
# rm -d -r -f ./build && mkdir build
cmake -S . -B build #>>/dev/null
cmake --build build

WINEPATH=/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ wine ./build/HexGame.exe
