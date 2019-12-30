#!/bin/bash

cd squidDrone || exit
cd build_unittests || exit
# generate Coverage
make coverage
