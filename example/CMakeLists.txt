cmake_minimum_required(VERSION 3.14)

project(crc32Examples C CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(crc32 REQUIRED)
endif()

add_custom_target(run-examples)

function(add_example NAME)
  add_executable("${NAME}" "${NAME}.cpp")
  target_link_libraries("${NAME}" PRIVATE crc32::crc32)
#  target_compile_features("${NAME}" PRIVATE cxx_std_17)
  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

function(add_c_example NAME)
  add_executable("${NAME}" "${NAME}.c")
  target_link_libraries("${NAME}" PRIVATE crc32::crc32)
  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

function(add_example_thread NAME)
  add_executable("${NAME}" "${NAME}.cpp")
  target_link_libraries("${NAME}" PRIVATE crc32::crc32 Threads::Threads)
#  target_compile_features("${NAME}" PRIVATE cxx_std_17)
  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

add_example(crc32_test_singlethreaded)

add_example(simple_example)
add_c_example(simple_c_example)


set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)

if(Threads_FOUND)
  add_example_thread(crc32_test_multithreaded)
else()
message(WARNING "Threads not found ! Disable crc32_test_multithreaded example." )
endif()

add_folders(Example)
