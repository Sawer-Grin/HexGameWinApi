#!/bin/bash

clear && cd tests
cmake -S . -B build >>/dev/null
cmake --build build
cd build && ctest #--rerun-failed --output-on-failure
