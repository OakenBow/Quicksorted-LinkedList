cmake_minimum_required(VERSION 3.10)

project(Quicksorted_LinkedList)

file(GLOB_RECURSE LIB_SRCS "src/*.*pp")
add_library(QSLL ${LIB_SRCS})

add_executable(QSLL-Test test.cpp)
