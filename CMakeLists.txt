cmake_minimum_required(VERSION 3.10)
project(Quicksorted_LinkedList)
set(CMAKE_CXX_STANDARD 14)





file(GLOB_RECURSE LIB_SRCS "src/*.*pp")
add_library(QSLL ${LIB_SRCS})


INCLUDE_DIRECTORIES(include)
add_executable(QSLL-Test test.cpp)
target_link_libraries(QSLL-Test QSLL)
