cmake_minimum_required(VERSION 3.14)
project(GLO_Filter_Code)

set(CMAKE_CXX_STANDARD 14)

add_executable(GLO_Filter_Code main.cpp "Filters.cpp" pch.h CircularBuffer.hpp)