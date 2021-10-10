cmake_minimum_required(VERSION 3.19)
project(BT)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BT
        BinTree.cpp
        BinTree.h
        main.cpp)
