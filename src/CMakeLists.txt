cmake_minimum_required(VERSION 3.13)
project(myApp
    VERSION 1.0
    DESCRIPTION "A brief CMake experiment"
    LANGUAGES CXX)

target_compile_features(myApp PRIVATE cxx_std_17)

set(CXX_STANDARD_REQUIRED 17)

add_executable(cmake_testapp main.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_options(myApp PRIVATE /W4)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(myApp PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # other macOS-specific flags for Clang
endif()