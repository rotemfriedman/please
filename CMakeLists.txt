cmake_minimum_required(VERSION 3.10)
project(hw2-tree)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw2-tree main.cpp TreeAvl.h NodeAvl.h library.h library.cpp Exception.h)