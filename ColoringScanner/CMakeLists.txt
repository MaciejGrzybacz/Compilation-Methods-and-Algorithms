cmake_minimum_required(VERSION 3.29)
project(ColoringScanner)

set(CMAKE_CXX_STANDARD 20)

add_executable(ColoringScanner main.cpp
        impl/Scanner.cpp
        impl/Scanner.h
        main.cpp)
