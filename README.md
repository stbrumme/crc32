# Fast CRC32

This is a mirror of my CRC32 library hosted at https://create.stephan-brumme.com/crc32/

## Features

- C++11 support (C++17 recommended, eg **std::string_view** ...)
- CMake support (3.14 minimal)
- The fastest algorithms need about 1 CPU cycle per byte
- Endian-aware
- Support for [multi-threaded computation](example/crc32_test_multithreaded.cpp)
- Multi OS support: Linux 32/64, MacOS, Windows 32/64, Android 32/64
- Cross-plateform support: AMD64, I386, ARMv8, ARMv7, ARMv6, ARMv5, RISC-V 32/64, PPC64le, Mips, m68k..
- Runs even on [Arduino](Crc32Best.ino), Raspberry Pi, etc.
- Quite long posting about it on https://create.stephan-brumme.com/crc32/, describing each implemented algorithm in detail

## Algorithms

- bitwise
- branch-free bitwise
- half-byte
- tableless full-byte
- Sarwate's original algorithm
- slicing-by-4
- slicing-by-8
- slicing-by-16
- crc32_combine() "merges" two indepedently computed CRC32 values which is the basis for even faster multi-threaded calculation

See my website https://create.stephan-brumme.com/crc32/ for documentation, code examples and a benchmark.

# Building and installing

See the [BUILDING](BUILDING.md) document.

# Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

# Open source projects used

- [crc32](https://github.com/stbrumme/crc32)
- [dockcross](https://github.com/dockcross/dockcross)
- [crosstool-ng](https://github.com/crosstool-ng/crosstool-ng)
- [git](https://github.com/git/git)
- [cmake-init](https://github.com/friendlyanon/cmake-init)
- [buildroot](https://github.com/buildroot/buildroot)
- [CMake](https://github.com/Kitware/CMake)
- [llvm-project](https://github.com/llvm/llvm-project)
- [gcc](https://github.com/gcc-mirror/gcc)
- [docker](https://github.com/docker/docker)
- [actions](https://github.com/actions/virtual-environments)

# Licensing

See the [LICENSE](LICENSE) document.
