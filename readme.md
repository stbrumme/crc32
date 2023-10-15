# Fast CRC32

This is a mirror of my CRC32 library hosted at https://create.stephan-brumme.com/crc32/

Features in a nutshell:
- C++ code, single file
- the fastest algorithms need about 1 CPU cycle per byte
- endian-aware
- support for multi-threaded computation
- runs even on Arduino, Raspberry Pi, etc.
- quite long posting about it on https://create.stephan-brumme.com/crc32/, describing each implemented algorithm in detail

Algorithms:
- bitwise
- branch-free bitwise
- half-byte
- tableless full-byte
- Sarwate's original algorithm
- slicing-by-2
- slicing-by-4
- slicing-by-8
- slicing-by-16

- crc32_combine() "merges" two indepedently computed CRC32 values which is the basis for even faster multi-threaded calculation

See my website https://create.stephan-brumme.com/crc32/ for documentation, code examples and a benchmark.
