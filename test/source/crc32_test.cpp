// //////////////////////////////////////////////////////////
// crc32_test.cpp
// Copyright (c) 2011-2021 Stephan Brumme. All rights reserved.
// Google test contributed by Bensuperpc
// see http://create.stephan-brumme.com/disclaimer.html
//

#include <functional>  // std::function
#include <string>  // std::string
#include <vector>  // std::vector

#include "crc32/crc32.hpp"

#include "gtest/gtest.h"

extern "C" {
#include "crc32/crc32.h"
}

TEST(crc32, empty)
{
  const std::string str = "";
  const uint32_t expected_result = 0;

  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_bitwise_branch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise_branch(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise_branch(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str.data(), 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_halfbyte(str.data(), str.size(), 0));

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE

  EXPECT_EQ(expected_result, crc32::crc32_1byte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless2(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless2(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless2(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_8bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4x8bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_16bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_16bytes_prefetch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes_prefetch(str, 0));

  // C functions
  EXPECT_EQ(expected_result,
            crc32_16bytes_prefetch(str.data(), str.size(), 0, 256));
#endif

  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_fast(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
}

TEST(crc32, basic1)
{
  const std::string str = "SHA3-512";
  const uint32_t expected_result = 0x95980D67;

  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_bitwise_branch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise_branch(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise_branch(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_halfbyte(str.data(), str.size(), 0));

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE

  EXPECT_EQ(expected_result, crc32::crc32_1byte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless2(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless2(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless2(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_8bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4x8bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_16bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_16bytes_prefetch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes_prefetch(str, 0));

  // C functions
  EXPECT_EQ(expected_result,
            crc32_16bytes_prefetch(str.data(), str.size(), 0, 256));
#endif

  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_fast(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
}

TEST(crc32, basic2)
{
  const std::string str = "Linux";
  const uint32_t expected_result = 0x53D0684B;

  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_bitwise_branch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise_branch(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise_branch(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_halfbyte(str.data(), str.size(), 0));

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE

  EXPECT_EQ(expected_result, crc32::crc32_1byte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless2(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless2(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless2(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_8bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4x8bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_16bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_16bytes_prefetch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes_prefetch(str, 0));

  // C functions
  EXPECT_EQ(expected_result,
            crc32_16bytes_prefetch(str.data(), str.size(), 0, 256));
#endif

  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_fast(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
}

TEST(crc32, basic3)
{
  const std::string str = "CRC32";
  const uint32_t expected_result = 0xF6151584;

  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_bitwise_branch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise_branch(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise_branch(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_halfbyte(str.data(), str.size(), 0));

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE

  EXPECT_EQ(expected_result, crc32::crc32_1byte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless2(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless2(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless2(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_8bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4x8bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_16bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_16bytes_prefetch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes_prefetch(str, 0));

  // C functions
  EXPECT_EQ(expected_result,
            crc32_16bytes_prefetch(str.data(), str.size(), 0, 256));
#endif

  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_fast(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
}

TEST(crc32, basic4)
{
  const std::string str = "0123456789";
  const uint32_t expected_result = 0xA684C7C6;

  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_bitwise_branch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise_branch(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise_branch(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_halfbyte(str.data(), str.size(), 0));

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE

  EXPECT_EQ(expected_result, crc32::crc32_1byte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless2(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless2(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless2(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_8bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4x8bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_16bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_16bytes_prefetch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes_prefetch(str, 0));

  // C functions
  EXPECT_EQ(expected_result,
            crc32_16bytes_prefetch(str.data(), str.size(), 0, 256));
#endif

  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_fast(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
}

TEST(crc32, basic5)
{
  const std::string str = "LGBTQIA+";
  const uint32_t expected_result = 0x5C9BD8DC;

  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_bitwise_branch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise_branch(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise_branch(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_halfbyte(str.data(), str.size(), 0));

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE

  EXPECT_EQ(expected_result, crc32::crc32_1byte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless2(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless2(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless2(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_8bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4x8bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_16bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_16bytes_prefetch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes_prefetch(str, 0));

  // C functions
  EXPECT_EQ(expected_result,
            crc32_16bytes_prefetch(str.data(), str.size(), 0, 256));
#endif

  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_fast(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
}

TEST(crc32, basic6)
{
  const std::string str = "Intergouvernementalisations";
  const uint32_t expected_result = 0x5DD186B5;

  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_bitwise_branch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_bitwise_branch(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_bitwise_branch(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_halfbyte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_halfbyte(str.data(), str.size(), 0));

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE

  EXPECT_EQ(expected_result, crc32::crc32_1byte(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_1byte_tableless2(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_1byte_tableless2(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_1byte_tableless2(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_8bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_4x8bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_4x8bytes(str.data(), str.size(), 0));
#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32_16bytes(str.data(), str.size(), 0));

  EXPECT_EQ(expected_result,
            crc32::crc32_16bytes_prefetch(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_16bytes_prefetch(str, 0));

  // C functions
  EXPECT_EQ(expected_result,
            crc32_16bytes_prefetch(str.data(), str.size(), 0, 256));
#endif

  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
  EXPECT_EQ(expected_result, crc32::crc32_fast(str, 0));

  // C functions
  EXPECT_EQ(expected_result, crc32::crc32_fast(str.data(), str.size(), 0));
}

TEST(crc32, advanced1)
{
  const std::string str = "git";
  const uint32_t expected_result = 0x518E617C;

  uint32_t result = 0;

  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes_prefetch(s.data(), 1, result, 256);
  }
  EXPECT_EQ(expected_result, result);

#endif

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);
}

TEST(crc32, advanced2)
{
  const std::string str = "ubuntu";
  const uint32_t expected_result = 0x7C4B9639;

  uint32_t result = 0;

  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes_prefetch(s.data(), 1, result, 256);
  }
  EXPECT_EQ(expected_result, result);

#endif

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);
}

TEST(crc32, advanced3)
{
  const std::string str = "Pneumonoultramicroscopicsilicovolcanoconiosis";
  const uint32_t expected_result = 0xD57FFD71;

  uint32_t result = 0;

  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes_prefetch(s.data(), 1, result, 256);
  }
  EXPECT_EQ(expected_result, result);

#endif

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);
}

TEST(crc32, advanced4)
{
  const std::string str = "azertyuiopqsdfghjklmwxcvbn";
  const uint32_t expected_result = 0xF36868CC;

  uint32_t result = 0;

  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes_prefetch(s.data(), 1, result, 256);
  }
  EXPECT_EQ(expected_result, result);

#endif

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);
}

TEST(crc32, advanced5)
{
  const std::string str = "+-*/#~|{}()=.,[]?;:!";
  const uint32_t expected_result = 0x98783B28;

  uint32_t result = 0;

  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_bitwise_branch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_bitwise_branch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_halfbyte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_halfbyte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_1byte_tableless2(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_1byte_tableless2(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_4x8bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_4x8bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

#endif

#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_16bytes_prefetch(s.data(), 1, result, 256);
  }
  EXPECT_EQ(expected_result, result);

#endif

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_fast(s, result);
  }
  EXPECT_EQ(expected_result, result);

  // C functions
  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32_fast(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);
}

/*
TEST(crc32, advanced_test1)
{
  const std::string str = "windows11";
  const uint32_t expected_result = 0xD93DD2EE;

  uint32_t result = 0;

  const std::vector<std::function<uint32_t(const void*, size_t, const
uint32_t)>> crc32_function = {crc32::crc32_bitwise, crc32::crc32_bitwise_branch,
                        crc32::crc32_halfbyte,
#ifdef CRC32_USE_LOOKUP_TABLE_BYTE
                        crc32::crc32_1byte,
                        crc32::crc32_1byte_tableless,
                        crc32::crc32_1byte_tableless2,
#endif
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_4
                        crc32::crc32_4bytes,
#endif
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_8
                        crc32::crc32_8bytes,
                        crc32::crc32_4x8bytes,
#endif
#ifdef CRC32_USE_LOOKUP_TABLE_SLICING_BY_16
                        crc32::crc32_16bytes,
#endif
                        crc32::crc32_fast};

  for (const auto& function : crc32_function) {
    result = 0;
    for (const char& c : str) {
      const std::string s(1, c);
      result = function(s.data(), 1, result);
    }
    EXPECT_EQ(expected_result, result);
  }

  result = 0;
  for (const char& c : str) {
    const std::string s(1, c);
    result = crc32::crc32_16bytes_prefetch(s.data(), 1, result);
  }
  EXPECT_EQ(expected_result, result);
}
*/
