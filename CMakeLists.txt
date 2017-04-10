cmake_minimum_required(VERSION 3.7)
project(LazarusMailALess)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp main.h slave.cpp slave.h)
add_executable(LazarusMailALess ${SOURCE_FILES})