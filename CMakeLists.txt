cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    crc32
    VERSION 0.1.0
    DESCRIPTION "fast crc32 library"
    HOMEPAGE_URL "https://create.stephan-brumme.com/"
    LANGUAGES C CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Library options ----

option(CRC32_USE_LOOKUP_TABLE_BYTE "Enable 1 byte crc32 function" ON)
option(CRC32_USE_LOOKUP_TABLE_SLICING_BY_4 "Enable 4 byte crc32 function" ON)
option(CRC32_USE_LOOKUP_TABLE_SLICING_BY_8 "Enable 8 byte crc32 function" ON)
option(CRC32_USE_LOOKUP_TABLE_SLICING_BY_16 "Enable 16 byte crc32 function" ON)

# ---- Declare library ----

add_library(
    crc32_crc32
    source/crc32.cpp
    source/crc32.c
    source/crc32_var.c
)
add_library(crc32::crc32 ALIAS crc32_crc32)

include(GenerateExportHeader)
generate_export_header(
    crc32_crc32
    BASE_NAME crc32
    EXPORT_FILE_NAME export/crc32/crc32_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

# ---- Library variables ----

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(crc32_crc32 PUBLIC CRC32_STATIC_DEFINE)
endif()

if(CRC32_USE_LOOKUP_TABLE_BYTE)
  target_compile_definitions(crc32_crc32 PUBLIC CRC32_USE_LOOKUP_TABLE_BYTE)
else()
  message(STATUS "CRC32_USE_LOOKUP_TABLE_BYTE is disable")
endif()

if(CRC32_USE_LOOKUP_TABLE_SLICING_BY_4)
  target_compile_definitions(crc32_crc32 PUBLIC CRC32_USE_LOOKUP_TABLE_SLICING_BY_4)
else()
  message(STATUS "DCRC32_USE_LOOKUP_TABLE_SLICING_BY_4 is disable")
endif()

if(CRC32_USE_LOOKUP_TABLE_SLICING_BY_8)
  target_compile_definitions(crc32_crc32 PUBLIC CRC32_USE_LOOKUP_TABLE_SLICING_BY_8)
else()
  message(STATUS "DCRC32_USE_LOOKUP_TABLE_SLICING_BY_8 is disable")
endif()

if(CRC32_USE_LOOKUP_TABLE_SLICING_BY_16)
target_compile_definitions(crc32_crc32 PUBLIC CRC32_USE_LOOKUP_TABLE_SLICING_BY_16)
else()
  message(STATUS "DCRC32_USE_LOOKUP_TABLE_SLICING_BY_16 is disable")
endif()

# ---- Library properties ----

set_target_properties(
    crc32_crc32 PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME crc32
    OUTPUT_NAME crc32
)

target_include_directories(
    crc32_crc32 ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    crc32_crc32 SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

# target_compile_features(crc32_crc32 PUBLIC cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${crc32_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT crc32_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of crc32"
  )
endif()

include(cmake/dev-mode.cmake)
