
cmake_minimum_required(VERSION 3.13)
project(npuzzle)

set(CMAKE_CXX_STANDARD 17)
include_directories("src/Parser/")

set(SRC src/main.cc
        src/Parser/Parser.cc)

add_executable(npuzzle ${SRC})
