#!/bin/bash

set -euo pipefail

cd build_unittests || exit

GTEST_COLOR=1 GTEST_REPEAT=3 GTEST_SHUFFLE=1 ctest -j8 -C Debug -T test -V