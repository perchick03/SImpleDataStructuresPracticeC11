cmake_minimum_required(VERSION 3.13)
project(CodingPractice)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(CodingPractice main.cpp Complex.cpp Tests/TestComplext.cpp Complex.cpp Complex.h)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

target_link_libraries(CodingPractice gtest gtest_main)