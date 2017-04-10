cmake_minimum_required(VERSION 3.7)
project(LazarusMailALess)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp slave.cpp main.hpp slave.hpp)
add_executable(LazarusMailALess ${SOURCE_FILES})