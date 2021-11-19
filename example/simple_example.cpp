// //////////////////////////////////////////////////////////
// simple_example.cpp
// Copyright (c) 2021-2021 Stephan Brumme. All rights reserved.
// Simple example contributed by Bensuperpc
// see http://create.stephan-brumme.com/disclaimer.html
//

#include <iostream>
#include <string>

#include "crc32/crc32.hpp"

auto main() -> int
{
  const std::string str1 = "Linux";
  const auto result1 =
      crc32::crc32_halfbyte(str1.data(), str1.size(), 0);  // Use void* for data
  std::cout << "CRC32 of: " << str1 << " = 0x" << std::hex << result1
            << std::endl;

  const std::string str2 = "Linux";
  const auto result2 = crc32::crc32_halfbyte(
      str2, 0);  // Use std::string_view or std::string for data
  std::cout << "CRC32 of: " << str2 << " = 0x" << std::hex << result2
            << std::endl;

  return 0;
}
