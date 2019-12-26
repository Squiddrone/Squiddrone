#!/bin/bash

set -euo pipefail

cd squidDrone
mkdir -p build && cd build

# Configure
cmake ../ -DGOOGLE_TESTS=ON -DCODE_COVERAGE=ON -DCMAKE_TOOLCHAIN_FILE=../cmake/gcc_linux_toolchain.cmake
# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . -j "$(nproc)"
