cmake_minimum_required(VERSION 3.19)
project(OBST)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OBST
        BinTree.cpp
        BinTree.h
        BST.cpp
        BST.h
        main.cpp
        OBST.cpp
        OBST.h)
