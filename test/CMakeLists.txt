cmake_minimum_required(VERSION 3.21.4)
project(test LANGUAGES CXX)

set(CMAKE_INCLUDE_FLAG_CXX "-iquote")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -Ofast -ffast-math --std=c++17")

include_directories(..)

add_executable(demo  cmdline.cpp)

