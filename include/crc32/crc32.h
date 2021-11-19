// //////////////////////////////////////////////////////////
// crc32.h
// Copyright (c) 2011-2021 Stephan Brumme. All rights reserved.
// Slicing-by-16 contributed by Bulat Ziganshin
// Tableless bytewise CRC contributed by Hagai Gold
// see http://create.stephan-brumme.com/disclaimer.html
//

#ifndef CRC32_H_INCLUDED
#define CRC32_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// uint8_t, uint32_t, int32_t
#include <stdint.h>

#include "crc32/crc32_var.h"

// Needed, add CRC32_EXPORT before each function
#include "crc32/crc32_export.hpp"

// crc32_fast selects the fastest algorithm depending on flags
// (CRC32_USE_LOOKUP_...)
/// compute CRC32 using the fastest algorithm for large datasets on modern CPUs
CRC32_EXPORT uint32_t crc32_fast(const void* data,
                                 size_t length,
                                 const uint32_t);

/// merge two CRC32 such that result = crc32(dataB, lengthB, crc32(dataA,
/// lengthA))
CRC32_EXPORT uint32_t crc32_combine(uint32_t crcA,
                                    uint32_t crcB,
                                    size_t lengthB);

/// compute CRC32 (bitwise algorithm)
CRC32_EXPORT uint32_t crc32_bitwise(const void* data,
                                    size_t length,
                                    const uint32_t);

/// compute CRC32 (bitwise algorithm)
CRC32_EXPORT uint32_t crc32_bitwise_branch(const void* data,
                                           size_t length,
                                           const uint32_t);

/// compute CRC32 (half-byte algorithm)
CRC32_EXPORT uint32_t crc32_halfbyte(const void* data,
                                     size_t length,
                                     const uint32_t);

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
/// compute CRC32 (standard algorithm)
CRC32_EXPORT uint32_t crc32_1byte(const void* data,
                                  size_t length,
                                  const uint32_t);
#endif

/// compute CRC32 (byte algorithm) without lookup tables
CRC32_EXPORT uint32_t crc32_1byte_tableless(const void* data,
                                            size_t length,
                                            const uint32_t);
/// compute CRC32 (byte algorithm) without lookup tables
CRC32_EXPORT uint32_t crc32_1byte_tableless2(const void* data,
                                             size_t length,
                                             const uint32_t);

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4
/// compute CRC32 (Slicing-by-4 algorithm)
CRC32_EXPORT uint32_t crc32_4bytes(const void* data,
                                   size_t length,
                                   const uint32_t);
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
/// compute CRC32 (Slicing-by-8 algorithm)
CRC32_EXPORT uint32_t crc32_8bytes(const void* data,
                                   size_t length,
                                   const uint32_t);
/// compute CRC32 (Slicing-by-8 algorithm), unroll inner loop 4 times
CRC32_EXPORT uint32_t crc32_4x8bytes(const void* data,
                                     size_t length,
                                     const uint32_t);
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
/// compute CRC32 (Slicing-by-16 algorithm)
CRC32_EXPORT uint32_t crc32_16bytes(const void* data,
                                    size_t length,
                                    const uint32_t);
/// compute CRC32 (Slicing-by-16 algorithm, prefetch upcoming data blocks)
CRC32_EXPORT uint32_t crc32_16bytes_prefetch(const void* data,
                                             size_t length,
                                             const uint32_t,
                                             size_t prefetchAhead);
#endif

#ifdef __cplusplus
}
#endif

#endif  // CRC32_H_INCLUDED
