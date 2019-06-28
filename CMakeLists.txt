cmake_minimum_required(VERSION 3.13)
project(Exercis)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


add_executable(Exercis main.cpp Tests/TestSimpleVector.cpp SimpleVector.cpp SimpleVector.h SimpleList.h Tests/TestSimpleList.cpp)

target_link_libraries(Exercis gtest gtest_main)