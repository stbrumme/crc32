// //////////////////////////////////////////////////////////
// Crc32cl.cpp
// Author: Sven Gothel <sgothel@jausoft.com>
// Copyright (c) 2021 Gothel Software e.K. (same zlib license from Stephan Brumme)
// Copyright (c) 2016-2019 Stephan Brumme.
// see http://create.stephan-brumme.com/disclaimer.html
//

#include "Crc32.h"
#include <cstdlib>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#include <fstream>
#include <iostream>

#include <ctime>

#ifdef ENABLE_MT
    // Multithreading is incomplete
    // - CRC differs, combine works but depending on thread count differs :)
    // - Should use fixed thread pool and async ringbuffer for data
    //   so threads can wait until being signaled EOD
    //
    // C++11 multithreading
    #include <thread>
    #include <future>

    // //////////////////////////////////////////////////////////
    // run a CRC32 algorithm on multiple threads
    typedef uint32_t (*Crc32Algorithm)(const void* data, size_t length, uint32_t previousCrc32);
    // compute CRC32 of up to maxBlockSize bytes and start recursively a new thread for excess data
    static uint32_t asyncCrc32(Crc32Algorithm myCrc32, const void* data, size_t numBytes, size_t maxBlockSize)
    {
      // last block ?
      if (numBytes <= maxBlockSize) {
        return myCrc32(data, numBytes, 0); // we're done
      }

      // compute CRC of the remaining bytes in a separate thread
      auto dataLeft  = (const char*)data + maxBlockSize;
      auto bytesLeft =          numBytes - maxBlockSize;
      auto remainder = std::async(std::launch::async, asyncCrc32, myCrc32, dataLeft, bytesLeft, maxBlockSize);

      // compute CRC of the current block
      auto currentCrc   = myCrc32(data, maxBlockSize, 0);
      // get CRC of the remainder
      auto remainderCrc = remainder.get();
      // and merge both
      return crc32_combine(currentCrc, remainderCrc, bytesLeft);
    }
    // call: run(crc32_8bytes, data, NumBytes, 8) if you have an octocore CPU
    static uint32_t run(Crc32Algorithm myCrc32, const void* data, size_t numBytes, size_t numThreads = 0)
    {
      // run on all cores
      if (numThreads == 0) {
        numThreads = std::thread::hardware_concurrency();
      }

      // split data evenly, rounding up
      auto defaultBlocksize = (numBytes + numThreads - 1) / numThreads;

      return asyncCrc32(myCrc32, data, numBytes, defaultBlocksize);
    }
#endif // ENABLE_MT


// timing
static double seconds()
{
  timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  return now.tv_sec + now.tv_nsec / 1000000000.0;
}

void print_usage(const char*progname) {
#ifdef ENABLE_MT
    fprintf(stderr, "Usage %s [-v] [-bsz <buffer-size>] [-threads <thread-count>] <input-file>\n", progname);
#else // ENABLE_MT
    fprintf(stderr, "Usage %s [-v] [-bsz <buffer-size>] <input-file>\n", progname);
#endif // ENABLE_MT
}

int main(int argc, char**argv)
{
    int argi=0;

    bool verbose = false;
    int thread_count = 1; // minimum
    size_t buffer_size = 20*4096; // minimum 81920 (empiric most efficient on arm64, raspi4 single thread)

    for(int i=1; i<argc; i++) {
        if( 0 == strcmp("-v", argv[i]) ) {
            verbose=true;
        } else if( 0 == strcmp("-threads", argv[i]) && i+1<argc ) {
#ifdef ENABLE_MT
            const int v = atoi(argv[++i]);
            thread_count = std::max(0, v);
#else // ENABLE_MT
            print_usage(argv[0]);
            return -1;
#endif // ENABLE_MT
        } else if( 0 == strcmp("-bsz", argv[i]) && i+1<argc ) {
            const size_t v = atol(argv[++i]);
            buffer_size = std::max(buffer_size, v);
        } else if( 0 != strncmp("-", argv[i], 1) ) {
            break; // end of options
        }
        argi = i;
    }

    if( 1+argi >= argc ) {
        print_usage(argv[0]);
        return -1;
    }
    std::string input_file(argv[++argi]);
    std::ifstream in(input_file, std::ios::binary);
    if( !in ) {
        fprintf(stderr, "Error reading file %s\n", input_file.c_str());
        return -1;
    }
    std::vector<uint8_t> buffer;

    buffer.reserve(buffer_size);

    double startTime;
    if( verbose ) {
        startTime = seconds();
        fprintf(stderr, "  Using: buffer_size %zu, threads %d, ", buffer_size, thread_count);
        #ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
            fprintf(stderr, "LOOKUP_TABLE_SLICING_BY_16\n");
        #elif defined(CRC32_USE_LOOKUP_TABLE_SLICING_BY_8)
            fprintf(stderr, "LOOKUP_TABLE_SLICING_BY_8\n");
        #elif defined(CRC32_USE_LOOKUP_TABLE_SLICING_BY_4)
            fprintf(stderr, "LOOKUP_TABLE_SLICING_BY_4\n");
        #elif defined(CRC32_USE_LOOKUP_TABLE_BYTE)
            fprintf(stderr, "LOOKUP_TABLE_BYTE\n");
        #else
            fprintf(stderr, "HALFBYTE\n");
        #endif
    } else {
        startTime = 0;
    }

    uint32_t res = 0;
    uint64_t total = 0;
    bool has_more = in.good();
    uint64_t loops = 0;
    while( has_more ) {
        buffer.resize(buffer.capacity());

        in.read(reinterpret_cast<char*>(buffer.data()), buffer.capacity());
        const size_t got = static_cast<size_t>(in.gcount());
        buffer.resize(got);
        total += got;
        has_more = in.good();
#ifdef ENABLE_MT
        if( 1 >= thread_count ) {
            res = crc32_fast(reinterpret_cast<char*>(buffer.data()), got, res);
        } else {
            res = run(crc32_fast, reinterpret_cast<char*>(buffer.data()), got, thread_count);
        }
#else // ENABLE_MT
        res = crc32_fast(reinterpret_cast<char*>(buffer.data()), got, res);
#endif // ENABLE_MT
        loops++;
    }
    if ( verbose ) {
        double duration  = seconds() - startTime;
        fprintf(stderr, "  Duration %.3fs, %.3f MiB/s, %" PRIu64 " KiB/loop, %" PRIu64 " loops\n", duration, (total / (1024*1024)) / duration, (total / 1024) / loops, loops);
    }
    printf("%08x\n", res);
    return 0;
}
