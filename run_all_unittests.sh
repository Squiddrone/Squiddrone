#!/bin/bash

set -euo pipefail

cd build_unittests || exit

make all_tests
