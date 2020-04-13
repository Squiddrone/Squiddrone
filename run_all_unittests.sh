#!/bin/bash

set -euo pipefail

cd squidDrone || exit
cd build_unittests || exit

make all_tests
