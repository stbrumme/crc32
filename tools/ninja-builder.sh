#!/usr/bin/env bash

#export CC=/usr/bin/clang
#export CXX=/usr/bin/clang++

#--preset=dev --preset=dev-coverage -D CMAKE_BUILD_TYPE=Release -D CMAKE_CXX_STANDARD=17

cmake -S . -B build -G Ninja $*

ninja -C build

ctest --verbose --parallel $(nproc) --test-dir build
