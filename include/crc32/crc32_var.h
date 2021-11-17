// //////////////////////////////////////////////////////////
// crc32_var.h
// Copyright (c) 2011-2021 Stephan Brumme. All rights reserved.
// Slicing-by-16 contributed by Bulat Ziganshin
// Tableless bytewise CRC contributed by Hagai Gold
// see http://create.stephan-brumme.com/disclaimer.html
//

#ifndef CRC32_VAR_H_INCLUDED
#define CRC32_VAR_H_INCLUDED

// if running on an embedded system, you might consider shrinking the
// big Crc32Lookup table by undefining these lines:

// #define CRC32_USE_LOOKUP_TABLE_BYTE
// #define CRC32_USE_LOOKUP_TABLE_SLICING_BY_4
// #define CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
// #define CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

// - crc32_bitwise  doesn't need it at all
// - crc32_bitwise_branch  doesn't need it at all
// - crc32_halfbyte has its own small lookup table
// - crc32_1byte_tableless and crc32_1byte_tableless2 don't need it at all
// - crc32_1byte    needs only Crc32Lookup[0]
// - crc32_4bytes   needs only Crc32Lookup[0..3]
// - crc32_8bytes   needs only Crc32Lookup[0..7]
// - crc32_4x8bytes needs only Crc32Lookup[0..7]
// - crc32_16bytes  needs all of Crc32Lookup
// using the aforementioned #defines the table is automatically fitted to your
// needs

// Needed, add CRC32_EXPORT before each function
#include "crc32/crc32_export.hpp"

// uint8_t, uint32_t, int32_t
#include <stdint.h>

#ifndef __LITTLE_ENDIAN
#  define __LITTLE_ENDIAN 1234
#endif
#ifndef __BIG_ENDIAN
#  define __BIG_ENDIAN 4321
#endif

// define endianness and some integer data types
#if defined(_MSC_VER) || defined(__MINGW32__)
// Windows always little endian
#  define __BYTE_ORDER __LITTLE_ENDIAN

// intrinsics / prefetching
#  if defined(__MINGW32__) || defined(__clang__)
#    define PREFETCH(location) __builtin_prefetch(location)
#  else
#    if defined(__SSE2__)
#      include <xmmintrin.h>
#      define PREFETCH(location) _mm_prefetch(location, _MM_HINT_T0)
#    else
#      define PREFETCH(location) ;
#    endif
#  endif
#else
// defines __BYTE_ORDER as __LITTLE_ENDIAN or __BIG_ENDIAN
#  include <sys/param.h>

// intrinsics / prefetching
#  ifdef __GNUC__
#    define PREFETCH(location) __builtin_prefetch(location)
#  else
// no prefetching
#    define PREFETCH(location) ;
#  endif
#endif

// abort if byte order is undefined
#if !defined(__BYTE_ORDER)

#  if _MSC_VER && !__INTEL_COMPILER
#    pragma message( \
        "undefined byte order, compile with -D__BYTE_ORDER=1234 (if little endian) or -D__BYTE_ORDER=4321 (big endian)")
#    pragma message("use default byte order: little endian (x86 and ARM CPUs)")
#  else
#    warning undefined byte order, compile with -D__BYTE_ORDER=1234 (if little endian) or -D__BYTE_ORDER=4321 (big endian)
#    warning use default byte order: little endian (x86 and ARM CPUs)
#  endif
#endif

#if __BYTE_ORDER == __BIG_ENDIAN
/// swap endianness
static inline uint32_t swap(uint32_t x)
{
#  if defined(__GNUC__) || defined(__clang__)
  return __builtin_bswap32(x);
#  else
  return (x >> 24) | ((x >> 8) & 0x0000FF00) | ((x << 8) & 0x00FF0000)
      | (x << 24);
#  endif
}
#endif

// //////////////////////////////////////////////////////////
// constants

/// zlib's CRC32 polynomial
extern const uint32_t Polynomial;

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
extern const uint32_t Crc32Lookup[16][256];
#elif defined(CRC32_USE_LOOKUP_TABLE_SLICING_BY_8)
extern const uint32_t Crc32Lookup[8][256];
#elif defined(CRC32_USE_LOOKUP_TABLE_SLICING_BY_4)
extern const uint32_t Crc32Lookup[4][256];
#elif defined(CRC32_USE_LOOKUP_TABLE_BYTE)
extern const uint32_t Crc32Lookup[1][256];
#else
#  define NO_LUT  // don't need Crc32Lookup at all
#endif
#endif  // CRC32_VAR_H_INCLUDED
