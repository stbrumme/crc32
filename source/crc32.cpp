// //////////////////////////////////////////////////////////
// crc32.cpp
// Copyright (c) 2011-2021 Stephan Brumme. All rights reserved.
// Slicing-by-16 contributed by Bulat Ziganshin
// Tableless bytewise CRC contributed by Hagai Gold
// see http://create.stephan-brumme.com/disclaimer.html
//

// if running on an embedded system, you might consider shrinking the
// big crc32_global_crc32Lookup table:
// - crc32_bitwise  doesn't need it at all
// - crc32_bitwise_banch doesn't need it at all
// - crc32_halfbyte has its own small lookup table
// - crc32_1byte    needs only crc32_global_crc32Lookup[0]
// - crc32_4bytes   needs only crc32_global_crc32Lookup[0..3]
// - crc32_8bytes   needs only crc32_global_crc32Lookup[0..7]
// - crc32_4x8bytes needs only crc32_global_crc32Lookup[0..7]
// - crc32_16bytes  needs all of crc32_global_crc32Lookup

#include "crc32/crc32.hpp"

/// compute CRC32 (bitwise algorithm)
uint32_t crc32::crc32_bitwise(const void* data,
                              size_t length,
                              const uint32_t previousCrc32)
{
  return ::crc32_bitwise(data, length, previousCrc32);
}

/// compute CRC32 (bitwise algorithm with branching)
uint32_t crc32::crc32_bitwise_branch(const void* data,
                                     size_t length,
                                     const uint32_t previousCrc32)
{
  return ::crc32_bitwise_branch(data, length, previousCrc32);
}

/// compute CRC32 (half-byte algorithm)
uint32_t crc32::crc32_halfbyte(const void* data,
                               size_t length,
                               const uint32_t previousCrc32)
{
  return ::crc32_halfbyte(data, length, previousCrc32);
}

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
/// compute CRC32 (standard algorithm)
uint32_t crc32::crc32_1byte(const void* data,
                            size_t length,
                            const uint32_t previousCrc32)
{
  return ::crc32_1byte(data, length, previousCrc32);
}
#endif

/// compute CRC32 (byte algorithm) without lookup tables
uint32_t crc32::crc32_1byte_tableless(const void* data,
                                      size_t length,
                                      const uint32_t previousCrc32)
{
  return ::crc32_1byte_tableless(data, length, previousCrc32);
}

/// compute CRC32 (byte algorithm) without lookup tables
uint32_t crc32::crc32_1byte_tableless2(const void* data,
                                       size_t length,
                                       const uint32_t previousCrc32)
{
  return ::crc32_1byte_tableless2(data, length, previousCrc32);
}

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4
/// compute CRC32 (Slicing-by-4 algorithm)
uint32_t crc32::crc32_4bytes(const void* data,
                             size_t length,
                             const uint32_t previousCrc32)
{
  return ::crc32_4bytes(data, length, previousCrc32);
}
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
/// compute CRC32 (Slicing-by-8 algorithm)
uint32_t crc32::crc32_8bytes(const void* data,
                             size_t length,
                             const uint32_t previousCrc32)
{
  return ::crc32_8bytes(data, length, previousCrc32);
}

/// compute CRC32 (Slicing-by-8 algorithm), unroll inner loop 4 times
uint32_t crc32::crc32_4x8bytes(const void* data,
                               size_t length,
                               const uint32_t previousCrc32)
{
  return ::crc32_4x8bytes(data, length, previousCrc32);
}
#endif  // CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
/// compute CRC32 (Slicing-by-16 algorithm)
uint32_t crc32::crc32_16bytes(const void* data,
                              size_t length,
                              const uint32_t previousCrc32)
{
  return ::crc32_16bytes(data, length, previousCrc32);
}

/// compute CRC32 (Slicing-by-16 algorithm, prefetch upcoming data blocks)
uint32_t crc32::crc32_16bytes_prefetch(const void* data,
                                       size_t length,
                                       const uint32_t previousCrc32,
                                       size_t prefetchAhead)
{
  return ::crc32_16bytes_prefetch(data, length, previousCrc32, prefetchAhead);
}
#endif

/// compute CRC32 using the fastest algorithm for large datasets on modern CPUs
uint32_t crc32::crc32_fast(const void* data,
                           size_t length,
                           const uint32_t previousCrc32)
{
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
  return crc32_16bytes(data, length, previousCrc32);
#elif defined(CRC32_USE_LOOKUP_TABLE_SLICING_BY_8)
  return crc32_8bytes(data, length, previousCrc32);
#elif defined(CRC32_USE_LOOKUP_TABLE_SLICING_BY_4)
  return crc32_4bytes(data, length, previousCrc32);
#elif defined(CRC32_USE_LOOKUP_TABLE_BYTE)
  return crc32_1byte(data, length, previousCrc32);
#else
  return crc32::crc32_halfbyte(data, length, previousCrc32);
#endif
}

/// merge two CRC32 such that result = crc32(dataB, lengthB, crc32(dataA,
/// lengthA))
uint32_t crc32::crc32_combine(uint32_t crcA, uint32_t crcB, size_t lengthB)
{
  return ::crc32_combine(crcA, crcB, lengthB);
}

/// compute CRC32 (bitwise algorithm)
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_bitwise(std::string_view data,
                                   const uint32_t previousCrc32)
#else
std::uint32_t crc32::crc32_bitwise(const std::string& data,
                                   const uint32_t previousCrc32)
#endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  while (length-- != 0) {
    crc ^= *current++;

    for (int j = 0; j < 8; j++) {
      // branch-free
      crc = (crc >> 1) ^ (-int32_t(crc & 1) & crc32_global_polynomial);
    }
  }

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}

/// compute CRC32 (bitwise algorithm with branching)
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_bitwise_branch(std::string_view data,
                                          const uint32_t previousCrc32)
#else
std::uint32_t crc32::crc32_bitwise_branch(const std::string& data,
                                          const uint32_t previousCrc32)
#endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  while (length-- != 0) {
    crc ^= *current++;

    for (int j = 0; j < 8; j++) {
      // branching, much slower
      if (crc & 1) {
        crc = (crc >> 1) ^ crc32_global_polynomial;
      } else {
        crc = crc >> 1;
      }
    }
  }

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}

/// compute CRC32 (half-byte algorithm)
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_halfbyte(std::string_view data,
                                    const uint32_t previousCrc32)
#else
std::uint32_t crc32::crc32_halfbyte(const std::string& data,
                                    const uint32_t previousCrc32)
#endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  /// look-up table for half-byte, same as crc32Lookup[0][16*i]
  static const uint32_t _crc32_global_crc32Lookup16[16] = {0x00000000,
                                                           0x1DB71064,
                                                           0x3B6E20C8,
                                                           0x26D930AC,
                                                           0x76DC4190,
                                                           0x6B6B51F4,
                                                           0x4DB26158,
                                                           0x5005713C,
                                                           0xEDB88320,
                                                           0xF00F9344,
                                                           0xD6D6A3E8,
                                                           0xCB61B38C,
                                                           0x9B64C2B0,
                                                           0x86D3D2D4,
                                                           0xA00AE278,
                                                           0xBDBDF21C};

  while (length-- != 0) {
    crc = _crc32_global_crc32Lookup16[(crc ^ *current) & 0x0F] ^ (crc >> 4);
    crc = _crc32_global_crc32Lookup16[(crc ^ (*current >> 4)) & 0x0F]
        ^ (crc >> 4);
    current++;
  }

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
/// compute CRC32 (standard algorithm)
#  if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_1byte(std::string_view data,
                                 const uint32_t previousCrc32)
#  else
std::uint32_t crc32::crc32_1byte(const std::string& data,
                                 const uint32_t previousCrc32)
#  endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  while (length-- != 0)
    crc = (crc >> 8) ^ crc32_global_crc32Lookup[0][(crc & 0xFF) ^ *current++];

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}
#endif

/// compute CRC32 (byte algorithm) without lookup tables
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_1byte_tableless(std::string_view data,
                                           const uint32_t previousCrc32)
#else
std::uint32_t crc32::crc32_1byte_tableless(const std::string& data,
                                           const uint32_t previousCrc32)
#endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  while (length-- != 0) {
    uint8_t s = uint8_t(crc) ^ *current++;

    // Hagai Gold made me aware of this table-less algorithm and send me code

    // polynomial 0xEDB88320 can be written in binary as
    // 11101101101110001000001100100000b reverse the bits (or just assume bit 0
    // is the first one) and we have bits set at position 0, 1, 2, 4, 5, 7, 8,
    // 10, 11, 12, 16, 22, 23, 26
    // => those are the shift offsets:
    // crc = (crc >> 8) ^
    //       t ^
    //      (t >>  1) ^ (t >>  2) ^ (t >>  4) ^ (t >>  5) ^  // == y
    //      (t >>  7) ^ (t >>  8) ^ (t >> 10) ^ (t >> 11) ^  // == y >> 6
    //      (t >> 12) ^ (t >> 16) ^                          // == z
    //      (t >> 22) ^ (t >> 26) ^                          // == z >> 10
    //      (t >> 23);

    // the fastest I can come up with:
    uint32_t low = (s ^ (s << 6)) & 0xFF;
    uint32_t a = (low * ((1 << 23) + (1 << 14) + (1 << 2)));
    crc = (crc >> 8) ^ (low * ((1 << 24) + (1 << 16) + (1 << 8))) ^ a ^ (a >> 1)
        ^ (low * ((1 << 20) + (1 << 12))) ^ (low << 19) ^ (low << 17)
        ^ (low >> 2);

    // Hagai's code:
    /*uint32_t t = (s ^ (s << 6)) << 24;

    // some temporaries to optimize XOR
    uint32_t x = (t >> 1) ^ (t >> 2);
    uint32_t y = x ^ (x >> 3);
    uint32_t z = (t >> 12) ^ (t >> 16);

    crc = (crc >> 8) ^
           t ^ (t >> 23) ^
           y ^ (y >>  6) ^
           z ^ (z >> 10);*/
  }

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}

/// compute CRC32 (byte algorithm) without lookup tables
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_1byte_tableless2(std::string_view data,
                                            const uint32_t previousCrc32)
#else
std::uint32_t crc32::crc32_1byte_tableless2(const std::string& data,
                                            const uint32_t previousCrc32)
#endif
{
  int32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  while (length-- != 0) {
    crc = crc ^ *current++;

    uint32_t c =
        (((crc << 31) >> 31)
         & ((crc32_global_polynomial >> 7) ^ (crc32_global_polynomial >> 1)))
        ^ (((crc << 30) >> 31)
           & ((crc32_global_polynomial >> 6) ^ crc32_global_polynomial))
        ^ (((crc << 29) >> 31) & (crc32_global_polynomial >> 5))
        ^ (((crc << 28) >> 31) & (crc32_global_polynomial >> 4))
        ^ (((crc << 27) >> 31) & (crc32_global_polynomial >> 3))
        ^ (((crc << 26) >> 31) & (crc32_global_polynomial >> 2))
        ^ (((crc << 25) >> 31) & (crc32_global_polynomial >> 1))
        ^ (((crc << 24) >> 31) & crc32_global_polynomial);

    crc = (static_cast<uint32_t>(crc) >> 8)
        ^ c;  // convert to unsigned integer before right shift
  }

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4
/// compute CRC32 (Slicing-by-4 algorithm)
#  if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_4bytes(std::string_view data,
                                  const uint32_t previousCrc32)
#  else
std::uint32_t crc32::crc32_4bytes(const std::string& data,
                                  const uint32_t previousCrc32)
#  endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint32_t* current = reinterpret_cast<const uint32_t*>(data.data());
  uint64_t length = data.length();

  // process four bytes at once (Slicing-by-4)
  while (length >= 4) {
#  if __BYTE_ORDER == __BIG_ENDIAN
    uint32_t one = *current++ ^ swap(crc);
    crc = crc32_global_crc32Lookup[0][one & 0xFF]
        ^ crc32_global_crc32Lookup[1][(one >> 8) & 0xFF]
        ^ crc32_global_crc32Lookup[2][(one >> 16) & 0xFF]
        ^ crc32_global_crc32Lookup[3][(one >> 24) & 0xFF];
#  else
    uint32_t one = *current++ ^ crc;
    crc = crc32_global_crc32Lookup[0][(one >> 24) & 0xFF]
        ^ crc32_global_crc32Lookup[1][(one >> 16) & 0xFF]
        ^ crc32_global_crc32Lookup[2][(one >> 8) & 0xFF]
        ^ crc32_global_crc32Lookup[3][one & 0xFF];
#  endif

    length -= 4;
  }

  const uint8_t* currentChar = reinterpret_cast<const uint8_t*>(current);
  // remaining 1 to 3 bytes (standard algorithm)
  while (length-- != 0)
    crc =
        (crc >> 8) ^ crc32_global_crc32Lookup[0][(crc & 0xFF) ^ *currentChar++];

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
/// compute CRC32 (Slicing-by-8 algorithm)
#  if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_8bytes(std::string_view data,
                                  const uint32_t previousCrc32)
#  else
std::uint32_t crc32::crc32_8bytes(const std::string& data,
                                  const uint32_t previousCrc32)
#  endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint32_t* current = reinterpret_cast<const uint32_t*>(data.data());
  uint64_t length = data.length();

  // process eight bytes at once (Slicing-by-8)
  while (length >= 8) {
#  if __BYTE_ORDER == __BIG_ENDIAN
    uint32_t one = *current++ ^ swap(crc);
    uint32_t two = *current++;
    crc = crc32_global_crc32Lookup[0][two & 0xFF]
        ^ crc32_global_crc32Lookup[1][(two >> 8) & 0xFF]
        ^ crc32_global_crc32Lookup[2][(two >> 16) & 0xFF]
        ^ crc32_global_crc32Lookup[3][(two >> 24) & 0xFF]
        ^ crc32_global_crc32Lookup[4][one & 0xFF]
        ^ crc32_global_crc32Lookup[5][(one >> 8) & 0xFF]
        ^ crc32_global_crc32Lookup[6][(one >> 16) & 0xFF]
        ^ crc32_global_crc32Lookup[7][(one >> 24) & 0xFF];
#  else
    uint32_t one = *current++ ^ crc;
    uint32_t two = *current++;
    crc = crc32_global_crc32Lookup[0][(two >> 24) & 0xFF]
        ^ crc32_global_crc32Lookup[1][(two >> 16) & 0xFF]
        ^ crc32_global_crc32Lookup[2][(two >> 8) & 0xFF]
        ^ crc32_global_crc32Lookup[3][two & 0xFF]
        ^ crc32_global_crc32Lookup[4][(one >> 24) & 0xFF]
        ^ crc32_global_crc32Lookup[5][(one >> 16) & 0xFF]
        ^ crc32_global_crc32Lookup[6][(one >> 8) & 0xFF]
        ^ crc32_global_crc32Lookup[7][one & 0xFF];
#  endif

    length -= 8;
  }

  const uint8_t* currentChar = reinterpret_cast<const uint8_t*>(current);
  // remaining 1 to 7 bytes (standard algorithm)
  while (length-- != 0)
    crc =
        (crc >> 8) ^ crc32_global_crc32Lookup[0][(crc & 0xFF) ^ *currentChar++];

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}

/// compute CRC32 (Slicing-by-8 algorithm), unroll inner loop 4 times
#  if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_4x8bytes(std::string_view data,
                                    const uint32_t previousCrc32)
#  else
std::uint32_t crc32::crc32_4x8bytes(const std::string& data,
                                    const uint32_t previousCrc32)
#  endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  // enabling optimization (at least -O2) automatically unrolls the inner
  // for-loop
  const size_t Unroll = 4;
  const size_t BytesAtOnce = 8 * Unroll;

  // process 4x eight bytes at once (Slicing-by-8)
  while (length >= BytesAtOnce) {
    for (size_t unrolling = 0; unrolling < Unroll; unrolling++) {
#  if __BYTE_ORDER == __BIG_ENDIAN
      uint32_t one = *current++ ^ swap(crc);
      uint32_t two = *current++;
      crc = crc32_global_crc32Lookup[0][two & 0xFF]
          ^ crc32_global_crc32Lookup[1][(two >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[2][(two >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[3][(two >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[4][one & 0xFF]
          ^ crc32_global_crc32Lookup[5][(one >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[6][(one >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[7][(one >> 24) & 0xFF];
#  else
      uint32_t one = *current++ ^ crc;
      uint32_t two = *current++;
      crc = crc32_global_crc32Lookup[0][(two >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[1][(two >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[2][(two >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[3][two & 0xFF]
          ^ crc32_global_crc32Lookup[4][(one >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[5][(one >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[6][(one >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[7][one & 0xFF];
#  endif
    }

    length -= BytesAtOnce;
  }

  const uint8_t* currentChar = reinterpret_cast<const uint8_t*>(current);
  // remaining 1 to 31 bytes (standard algorithm)
  while (length-- != 0)
    crc =
        (crc >> 8) ^ crc32_global_crc32Lookup[0][(crc & 0xFF) ^ *currentChar++];

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}
#endif  // CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
/// compute CRC32 (Slicing-by-16 algorithm)
#  if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_16bytes(std::string_view data,
                                   const uint32_t previousCrc32)
#  else
std::uint32_t crc32::crc32_16bytes(const std::string& data,
                                   const uint32_t previousCrc32)
#  endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  // enabling optimization (at least -O2) automatically unrolls the inner
  // for-loop
  const size_t Unroll = 4;
  const size_t BytesAtOnce = 16 * Unroll;

  while (length >= BytesAtOnce) {
    for (size_t unrolling = 0; unrolling < Unroll; unrolling++) {
#  if __BYTE_ORDER == __BIG_ENDIAN
      uint32_t one = *current++ ^ swap(crc);
      uint32_t two = *current++;
      uint32_t three = *current++;
      uint32_t four = *current++;
      crc = crc32_global_crc32Lookup[0][four & 0xFF]
          ^ crc32_global_crc32Lookup[1][(four >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[2][(four >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[3][(four >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[4][three & 0xFF]
          ^ crc32_global_crc32Lookup[5][(three >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[6][(three >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[7][(three >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[8][two & 0xFF]
          ^ crc32_global_crc32Lookup[9][(two >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[10][(two >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[11][(two >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[12][one & 0xFF]
          ^ crc32_global_crc32Lookup[13][(one >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[14][(one >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[15][(one >> 24) & 0xFF];
#  else
      uint32_t one = *current++ ^ crc;
      uint32_t two = *current++;
      uint32_t three = *current++;
      uint32_t four = *current++;
      crc = crc32_global_crc32Lookup[0][(four >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[1][(four >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[2][(four >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[3][four & 0xFF]
          ^ crc32_global_crc32Lookup[4][(three >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[5][(three >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[6][(three >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[7][three & 0xFF]
          ^ crc32_global_crc32Lookup[8][(two >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[9][(two >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[10][(two >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[11][two & 0xFF]
          ^ crc32_global_crc32Lookup[12][(one >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[13][(one >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[14][(one >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[15][one & 0xFF];
#  endif
    }

    length -= BytesAtOnce;
  }

  const uint8_t* currentChar = reinterpret_cast<const uint8_t*>(current);
  // remaining 1 to 63 bytes (standard algorithm)
  while (length-- != 0) {
    crc =
        (crc >> 8) ^ crc32_global_crc32Lookup[0][(crc & 0xFF) ^ *currentChar++];
  }

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}

/// compute CRC32 (Slicing-by-16 algorithm, prefetch upcoming data blocks)
#  if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_16bytes_prefetch(std::string_view data,
                                            const uint32_t previousCrc32,
                                            size_t prefetchAhead)
#  else
std::uint32_t crc32::crc32_16bytes_prefetch(const std::string& data,
                                            const uint32_t previousCrc32,
                                            size_t prefetchAhead)
#  endif
{
  uint32_t crc = ~previousCrc32;  // same as previousCrc32 ^ 0xFFFFFFFF
  const uint8_t* current = reinterpret_cast<const uint8_t*>(data.data());
  uint64_t length = data.length();

  // CRC code is identical to crc32_16bytes (including unrolling), only added
  // prefetching 256 bytes look-ahead seems to be the sweet spot on Core i7 CPUs

  // enabling optimization (at least -O2) automatically unrolls the for-loop
  const size_t Unroll = 4;
  const size_t BytesAtOnce = 16 * Unroll;

  while (length >= BytesAtOnce + prefetchAhead) {
    PREFETCH((reinterpret_cast<const char*>(current)) + prefetchAhead);

    for (size_t unrolling = 0; unrolling < Unroll; unrolling++) {
#  if __BYTE_ORDER == __BIG_ENDIAN
      uint32_t one = *current++ ^ swap(crc);
      uint32_t two = *current++;
      uint32_t three = *current++;
      uint32_t four = *current++;
      crc = crc32_global_crc32Lookup[0][four & 0xFF]
          ^ crc32_global_crc32Lookup[1][(four >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[2][(four >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[3][(four >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[4][three & 0xFF]
          ^ crc32_global_crc32Lookup[5][(three >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[6][(three >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[7][(three >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[8][two & 0xFF]
          ^ crc32_global_crc32Lookup[9][(two >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[10][(two >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[11][(two >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[12][one & 0xFF]
          ^ crc32_global_crc32Lookup[13][(one >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[14][(one >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[15][(one >> 24) & 0xFF];
#  else
      uint32_t one = *current++ ^ crc;
      uint32_t two = *current++;
      uint32_t three = *current++;
      uint32_t four = *current++;
      crc = crc32_global_crc32Lookup[0][(four >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[1][(four >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[2][(four >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[3][four & 0xFF]
          ^ crc32_global_crc32Lookup[4][(three >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[5][(three >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[6][(three >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[7][three & 0xFF]
          ^ crc32_global_crc32Lookup[8][(two >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[9][(two >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[10][(two >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[11][two & 0xFF]
          ^ crc32_global_crc32Lookup[12][(one >> 24) & 0xFF]
          ^ crc32_global_crc32Lookup[13][(one >> 16) & 0xFF]
          ^ crc32_global_crc32Lookup[14][(one >> 8) & 0xFF]
          ^ crc32_global_crc32Lookup[15][one & 0xFF];
#  endif
    }

    length -= BytesAtOnce;
  }

  const uint8_t* currentChar = reinterpret_cast<const uint8_t*>(current);
  // remaining 1 to 63 bytes (standard algorithm)
  while (length-- != 0) {
    crc =
        (crc >> 8) ^ crc32_global_crc32Lookup[0][(crc & 0xFF) ^ *currentChar++];
  }

  return ~crc;  // same as crc ^ 0xFFFFFFFF
}
#endif

/// compute CRC32 using the fastest algorithm for large datasets on modern CPUs
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
std::uint32_t crc32::crc32_fast(std::string_view data,
                                const uint32_t previousCrc32)
#else
std::uint32_t crc32::crc32_fast(const std::string& data,
                                const uint32_t previousCrc32)
#endif
{
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
  return crc32_16bytes(data, previousCrc32);
#elif defined(CRC32_USE_LOOKUP_TABLE_SLICING_BY_8)
  return crc32_8bytes(data, previousCrc32);
#elif defined(CRC32_USE_LOOKUP_TABLE_SLICING_BY_4)
  return crc32_4bytes(data, previousCrc32);
#elif defined(CRC32_USE_LOOKUP_TABLE_BYTE)
  return crc32_1byte(data, previousCrc32);
#else
  return crc32::crc32_halfbyte(data, previousCrc32);
#endif
}
