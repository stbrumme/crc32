cmake_minimum_required(VERSION 3.14)

project(crc32Tests LANGUAGES C CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)
include(../cmake/windows-set-path.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(crc32 REQUIRED)
  enable_testing()
endif()

if(NOT WIN32)
  include(FetchContent)

  # Externally provided libraries
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main)

  FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG main)

  # set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  set(FOLDER_benchmark
      "gbenchmark"
      CACHE STRING "" FORCE)
  set(FOLDER_gtest
      "gtest"
      CACHE STRING "" FORCE)
  set(FOLDER_gmock
      "gmock"
      CACHE STRING "" FORCE)
  set(FOLDER_googletest-distribution
      "googletest-distribution"
      CACHE STRING "" FORCE)

  # Disable tests on gtest
  set(gtest_build_tests
      OFF
      CACHE BOOL "" FORCE)
  set(gtest_build_samples
      OFF
      CACHE BOOL "" FORCE)

  # Disable tests on google benchmark
  set(BENCHMARK_ENABLE_TESTING
      OFF
      CACHE BOOL "" FORCE)
  set(BENCHMARK_ENABLE_WERROR
      OFF
      CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest googlebenchmark)
  # Lib: gtest_main benchmark::benchmark benchmark::benchmark_main
  # target_compile_features(crc32_test PRIVATE cxx_std_17)

  add_executable(crc32_bench source/crc32_bench.cpp)
  target_link_libraries(crc32_bench PRIVATE crc32::crc32
                                            benchmark::benchmark_main)
  option(BENCHMARK_TEST "RUN bench test with tests" OFF)                                          

  if(BENCHMARK_TEST)
    add_test(NAME crc32_bench COMMAND crc32_bench)
  elseif()
    message(STATUS "Disable crc32_bench, Performance benchmark test only run on Release/RelWithDebInfo/MinSizeRel")
  endif()

  # windows_set_path(crc32_bench crc32::crc32 benchmark::benchmark_main)

  add_executable(crc32_test source/crc32_test.cpp)
  target_link_libraries(crc32_test PRIVATE crc32::crc32 gtest_main)
  add_test(NAME crc32_test COMMAND crc32_test)
  # windows_set_path(crc32_test crc32::crc32 gtest_main)

  add_folders(Test)
else()
  message(WARNING "Disable tests, only tested on Linux and MacOS x86_64")
endif()
