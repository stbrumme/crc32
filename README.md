# Fast CRC32
This is a mirror of my CRC32 library hosted at https://create.stephan-brumme.com/crc32/

## Features

- C99 and C++11 support (C++17 recommended, eg **std::string_view** ...)
- CMake support (3.14 minimal or 3.19 with preset)
- The fastest algorithms need about 1 CPU cycle per byte
- Endian-aware
- Support for [multi-threaded computation](example/crc32_test_multithreaded.cpp)
- Multi OS support: Linux 32/64, MacOS, Windows 32/64, Android 32/64
- Cross-plateform support: AMD64, I386, ARMv8, ARMv7, ARMv6, ARMv5, RISC-V 32/64, PPC64le, Mips, m68k..
- Runs even on [Arduino](Crc32Best.ino), Raspberry Pi, etc.
- Quite long posting about it on https://create.stephan-brumme.com/crc32/, describing each implemented algorithm in detail

## Algorithms

| Functions                                              | version | Published by     | CPU cycles/byte | Bits/iter | Table size | MB/s   |
| ------------------------------------------------------ | ------- | ---------------- | --------------- | --------- | ---------- | ------ |
| bitwise_branch / crc32::bitwise_branch                 | 1.0.0   | unknown          | 100             | 1         | -          | 170    |
| bitwise / crc32::bitwise                               | 1.0.0   | unknown          | 50 or 40        | 1         | -          | 190    |
| half-byte / crc32::half-byte                           | 1.0.0   | unknown          | 14              | 4         | 64 bytes   | 263    |
| crc32_1byte / crc32::crc32_1byte                       | 1.0.0   | Hagai Gold       | 8               | 8         | 1 KB       | 522    |
| crc32_1byte_tableless / crc32::crc32_1byte_tableless   | 1.0.0   | Henry S. Warren  | 18              | 8         | -          | 300    |
| crc32_1byte_tableless2 / crc32::crc32_1byte_tableless2 | 1.0.0   | Dilip V. Sarwate | 19              | 8         | -          | 170    |
| crc32_4bytes / crc32::crc32_4bytes                     | 1.0.0   | Intel Corp.      | 3 or 4          | 32        | 4 KB       | 1458   |
| crc32_8bytes / crc32::crc32_8bytes                     | 1.0.0   | Intel Corp.      | 3 or 4          | 64        | 8 KB       | 2629   |
| crc32_4x8bytes / crc32::crc32_4x8bytes                 | 1.0.0   | ?                | 1.75 or 2.25    | 256       | 8 KB       | 3003   |
| crc32_16bytes / crc32::crc32_16bytes                   | 1.0.0   | Bulat Ziganshin  | 1.1 or 1.5      | 128       | 16 KB      | 6027   |
| crc32_16bytes_prefetch / crc32::crc32_16bytes_prefetch | 1.0.0   | Bulat Ziganshin  | 1 or 1.5        | 512       | 8 KB       | 6102   |
| crc32_fast / crc32::crc32_fast                         | 1.0.0   | None             | varies          | varies    | varies     | varies |

Tested on Legion 5 Pro:
- Manjaro 21.1.6
- Clang 12.0.1
- Build type: Release
- CPU: AMD R7 5800H
- RAM: 32 GB DDR4 3200Mhz 22CL 8x
- Data: 1 GB

### Others function
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
