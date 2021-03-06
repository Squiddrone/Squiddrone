#!/bin/bash

set -euo pipefail

mkdir -p build && cd build

# Configure
cmake ../ -DGOOGLE_TESTS=OFF -DCODE_COVERAGE=OFF -DBUILD_DOC=ON -DCMAKE_TOOLCHAIN_FILE=../cmake/gnu_arm_stm32_toolchain.cmake
# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . -j "$(nproc)"
