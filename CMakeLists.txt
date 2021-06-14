cmake_minimum_required(VERSION 3.19)
project(C_ThreadPool )

set(CMAKE_XX_STANDARD 14 )

set(CMAKE_XX_FLAGS -pthread)

add_executable(C_ThreadPool main.cpp ThreadPool.c ThreadPool.h)