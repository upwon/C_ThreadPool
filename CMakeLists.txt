cmake_minimum_required(VERSION 3.19)
project(C_ThreadPool C)

set(CMAKE_C_STANDARD 11  )

set(CMAKE_C_FLAGS -pthread)


add_executable(C_ThreadPool main.c ThreadPool.c ThreadPool.h)