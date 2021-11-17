// //////////////////////////////////////////////////////////
// simple_example.c
// Copyright (c) 2021-2021 Stephan Brumme. All rights reserved.
// Simple example contributed by Bensuperpc
// see http://create.stephan-brumme.com/disclaimer.html
//

#include <stdint.h>
#include <stdio.h>

#include "crc32/crc32.h"

int main()
{
  char str[5] = {'L', 'i', 'n', 'u', 'x'};

  const uint32_t result = crc32_halfbyte(str, 5, 0);

  if (result == 0x53d0684b) {
    printf("0x%.4X\n", result);
  } else {
    printf("Error: wrong CRC32 value");
    return 1;
  }
  return 0;
}
