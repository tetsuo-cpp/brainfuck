cmake_minimum_required(VERSION 3.9)
project(brainfuck)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_executable(
  brainfuck
  main.cpp
  Brainfuck.cpp
  Brainfuck.h
  )
