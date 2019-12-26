#!/bin/bash

if [ ! -d "$HOME/arm-gcc-toolchain/bin" ]; then
  pushd .
  cd ~ || exit
  if [ ! -d "$HOME/arm-gcc-toolchain" ]; then
    mkdir arm-gcc-toolchain
  fi
  wget -O "$HOME/arm-gcc-toolchain/gcc.tar.bz2" "$GCC_URL"
  cd arm-gcc-toolchain || exit
  tar -jxf gcc.tar.bz2 --strip=1
  rm -f gcc.tar.bz2
  popd || exit
fi
