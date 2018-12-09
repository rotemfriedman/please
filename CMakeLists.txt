cmake_minimum_required(VERSION 3.10)
project(please)

set(CMAKE_CXX_STANDARD 11)

add_executable(please main.cpp StaticEye.h library2.h library2.cpp Exception.h ImageValue.h
        StaticEye.h Map.cpp Map.h
        TreeAvl.h NodeAvl.h)