# ---- Developer mode ----

# Developer mode enables targets and code paths in the CMake scripts that are
# only relevant for the developer(s) of crc32
# Targets necessary to build the project must be provided unconditionally, so
# consumers can trivially build and package the project
if(PROJECT_IS_TOP_LEVEL)
  option(crc32_DEVELOPER_MODE "Enable developer mode" OFF)
  option(BUILD_SHARED_LIBS "Build shared libs." OFF)
endif()

# ---- Suppress C4251 on Windows ----

# Please see include/crc32/crc32.hpp for more details
set(pragma_suppress_c4251 "#define CRC32_SUPPRESS_C4251")
if(MSVC)
  string(APPEND pragma_suppress_c4251 [[ _Pragma("warning(suppress:4251)")]])
endif()

# ---- Warning guard ----

# target_include_directories with the SYSTEM modifier will request the compiler
# to omit warnings from the provided paths, if the compiler supports that
# This is to provide a user experience similar to find_package when
# add_subdirectory or FetchContent is used to consume this project
set(warning_guard "")
if(NOT PROJECT_IS_TOP_LEVEL)
  option(
      crc32_INCLUDES_WITH_SYSTEM
      "Use SYSTEM modifier for crc32's includes, disabling warnings"
      ON
  )
  mark_as_advanced(crc32_INCLUDES_WITH_SYSTEM)
  if(crc32_INCLUDES_WITH_SYSTEM)
    set(warning_guard SYSTEM)
  endif()
endif()
