#!/bin/bash

set -euo pipefail

cd squidDrone
mkdir -p build && cd build

# Configure
cmake ../ -DCMAKE_TOOLCHAIN_FILE=../cmake/gnu_arm_stm32_toolchain.cmake
# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . -j $(nproc)
