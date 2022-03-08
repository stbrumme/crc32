// //////////////////////////////////////////////////////////
// Crc32TestMultithreaded.cpp
// Copyright (c) 2021 Stephan Brumme. All rights reserved.
// see http://create.stephan-brumme.com/disclaimer.html
//

#include <chrono>  // std::chrono
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "crc32/crc32.hpp"

// C++11 multithreading
#include <future>
#include <thread>

// //////////////////////////////////////////////////////////
// test code

/// one gigabyte
const size_t NumBytes = 1024 * 1024 * 1024;

using cpp_clock = std::chrono::high_resolution_clock;

// //////////////////////////////////////////////////////////
// run a CRC32 algorithm on multiple threads
typedef uint32_t (*Crc32Algorithm)(const void* data,
                                   size_t length,
                                   uint32_t previousCrc32);
// compute CRC32 of up to maxBlockSize bytes and start recursively a new thread
// for excess data
uint32_t asyncCrc32(Crc32Algorithm myCrc32,
                    const void* data,
                    size_t numBytes,
                    size_t maxBlockSize)
{
  // last block ?
  if (numBytes <= maxBlockSize)
    return myCrc32(data, numBytes, 0);  // we're done

  // compute CRC of the remaining bytes in a separate thread
  auto dataLeft = reinterpret_cast<const char*>(data) + maxBlockSize;
  auto bytesLeft = numBytes - maxBlockSize;
  auto remainder = std::async(std::launch::async,
                              asyncCrc32,
                              myCrc32,
                              dataLeft,
                              bytesLeft,
                              maxBlockSize);

  // compute CRC of the current block
  auto currentCrc = myCrc32(data, maxBlockSize, 0);
  // get CRC of the remainder
  auto remainderCrc = remainder.get();
  // and merge both
  return crc32::crc32_combine(currentCrc, remainderCrc, bytesLeft);
}
// call: run(crc32_8bytes, data, NumBytes, 8) if you have an octocore CPU
uint32_t run(Crc32Algorithm myCrc32,
             const void* data,
             size_t numBytes,
             size_t numThreads = 0)
{
  // run on all cores
  if (numThreads == 0)
    numThreads = std::thread::hardware_concurrency();

  // split data evenly, rounding up
  auto defaultBlocksize = (numBytes + numThreads - 1) / numThreads;

  return asyncCrc32(myCrc32, data, numBytes, defaultBlocksize);
}

// test original sequential CRC32 algorithm against crc32_combine
bool testCombine(const char* data, size_t maxBytes = 1024)
{
  bool ok = true;
  for (size_t lengthA = 1; lengthA < maxBytes; lengthA++) {
    // split bytes into two blocks of lengthA and lengthB
    auto lengthB = maxBytes - lengthA;

// compute CRC of both blocks
#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
    auto crcA = crc32::crc32_1byte(data, lengthA);
    auto crcB = crc32::crc32_1byte(data + lengthA, lengthB);

    // CRC of the whole block
    auto crcAtOnce = crc32::crc32_1byte(data, maxBytes);
    // CRC of both blocks in a sequential fashion
    auto crcSequential = crc32::crc32_1byte(data + lengthA, lengthB, crcA);

    // CRC using the new crc32_combine function
    auto crcCombined = crc32::crc32_combine(crcA, crcB, lengthB);

    // check results
    if (crcAtOnce != crcSequential || crcAtOnce != crcCombined) {
      printf("FAILED @ %zu: %08X %08X %08X %08X %08X\n",
             lengthA,
             crcA,
             crcB,
             crcAtOnce,
             crcSequential,
             crcCombined);
      ok = false;
    }
#else
    auto crcA = crc32::crc32_halfbyte(data, lengthA);
    auto crcB = crc32::crc32_halfbyte(data + lengthA, lengthB);

    // CRC of the whole block
    auto crcAtOnce = crc32::crc32_halfbyte(data, maxBytes);
    // CRC of both blocks in a sequential fashion
    auto crcSequential = crc32::crc32_halfbyte(data + lengthA, lengthB, crcA);

    // CRC using the new crc32_combine function
    auto crcCombined = crc32::crc32_combine(crcA, crcB, lengthB);

    // check results
    if (crcAtOnce != crcSequential || crcAtOnce != crcCombined) {
      printf("FAILED @ %zu: %08X %08X %08X %08X %08X\n",
             lengthA,
             crcA,
             crcB,
             crcAtOnce,
             crcSequential,
             crcCombined);
      ok = false;
    }
#endif
  }
  return ok;
}

int main(int argc, char* argv[])
{
  // //////////////////////////////////////////////////////////
  printf("Please wait ...\n");

  uint32_t randomNumber = 0x27121978;
  // initialize
  char* data = new char[NumBytes];
  for (size_t i = 0; i < NumBytes; i++) {
    data[i] = char(randomNumber & 0xFF);
    // simple LCG, see
    // http://en.wikipedia.org/wiki/Linear_congruential_generator
    randomNumber = 1664525 * randomNumber + 1013904223;
  }

  // re-use variables
  auto start_time = cpp_clock::now();

  double duration = 0.0;
  uint32_t crc = 0;

  // number of threads: use all cores by default or set number as command-line
  // parameter
  auto numThreads = 0;
  if (argc == 2) {
    numThreads = std::stoi(argv[1]);
  }
  if (numThreads <= 0) {
    numThreads = std::thread::hardware_concurrency();
  }
  printf("use %d threads:\n", numThreads);

// //////////////////////////////////////////////////////////
// one byte at once
#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
  start_time = cpp_clock::now();
  crc = run(crc32::crc32_1byte, data, NumBytes, numThreads);
  duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                 cpp_clock::now() - start_time)
                 .count();
  printf("  1 byte  at once / %d threads: CRC=%08X, %.3fs, %.3f MB/s\n",
         numThreads,
         crc,
         duration,
         (NumBytes / (1024 * 1024)) / duration);
#endif

// four bytes at once
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4
  start_time = cpp_clock::now();
  crc = run(crc32::crc32_4bytes, data, NumBytes, numThreads);
  duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                 cpp_clock::now() - start_time)
                 .count();
  printf("  4 bytes at once / %d threads: CRC=%08X, %.3fs, %.3f MB/s\n",
         numThreads,
         crc,
         duration,
         (NumBytes / (1024 * 1024)) / duration);
#endif

// eight bytes at once
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
  start_time = cpp_clock::now();
  crc = run(crc32::crc32_8bytes, data, NumBytes, numThreads);
  duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                 cpp_clock::now() - start_time)
                 .count();
  printf("  8 bytes at once / %d threads: CRC=%08X, %.3fs, %.3f MB/s\n",
         numThreads,
         crc,
         duration,
         (NumBytes / (1024 * 1024)) / duration);

#endif

// eight bytes at once, unrolled 4 times (=> 32 bytes per loop)
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
  start_time = cpp_clock::now();
  crc = run(crc32::crc32_4x8bytes, data, NumBytes, numThreads);
  duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                 cpp_clock::now() - start_time)
                 .count();
  printf("4x8 bytes at once / %d threads: CRC=%08X, %.3fs, %.3f MB/s\n",
         numThreads,
         crc,
         duration,
         (NumBytes / (1024 * 1024)) / duration);
#endif

// sixteen bytes at once
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
  start_time = cpp_clock::now();
  crc = run(crc32::crc32_16bytes, data, NumBytes, numThreads);
  duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                 cpp_clock::now() - start_time)
                 .count();
  printf(" 16 bytes at once / %d threads: CRC=%08X, %.3fs, %.3f MB/s\n",
         numThreads,
         crc,
         duration,
         (NumBytes / (1024 * 1024)) / duration);
#endif

// //////////////////////////////////////////////////////////
// slowly increment number of threads to determine scalability
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
  printf("run slicing-by-8 algorithm with 1 to %d threads:\n", numThreads);
#else
  printf("run crc32_halfbyte algorithm with 1 to %d threads:\n", numThreads);
#endif

  for (auto scaleThreads = 1; scaleThreads <= numThreads; scaleThreads++) {
    // eight bytes at once
    start_time = cpp_clock::now();
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
    if (scaleThreads == 1) {
      crc = crc32::crc32_8bytes(data, NumBytes);  // single-threaded
    } else {
      crc = run(
          crc32::crc32_8bytes, data, NumBytes, scaleThreads);  // multi-threaded
    }
#else
    if (scaleThreads == 1) {
      crc = crc32::crc32_halfbyte(data, NumBytes);  // single-threaded
    } else {
      crc = run(crc32::crc32_halfbyte,
                data,
                NumBytes,
                scaleThreads);  // multi-threaded
    }
#endif

    duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                   cpp_clock::now() - start_time)
                   .count();
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
    printf("  8 bytes at once / %d threads: CRC=%08X, %.3fs, %.3f MB/s\n",
           scaleThreads,
           crc,
           duration,
           (NumBytes / (1024 * 1024)) / duration);
#else
    printf("  0.5 bytes at once / %d threads: CRC=%08X, %.3fs, %.3f MB/s\n",
           scaleThreads,
           crc,
           duration,
           (NumBytes / (1024 * 1024)) / duration);
#endif

    // //////////////////////////////////////////////////////////
    // verify crc32_combine
    if (!testCombine(data, 1024)) {
      printf("ERROR in crc32_combine !!!\n");
    }

    delete[] data;
    return 0;
  }
}
