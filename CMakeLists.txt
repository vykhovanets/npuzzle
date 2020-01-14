
cmake_minimum_required(VERSION 3.13)
project(npuzzle)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  piksel
  GIT_REPOSITORY https://github.com/bernhardfritz/piksel
)
FetchContent_Populate(piksel)
add_subdirectory(${piksel_SOURCE_DIR} ${piksel_BINARY_DIR})

set(SRC src/main.cc
        src/Log/log.cc
        src/UI/UI.cc
        src/Parser/Parser.cc)

add_executable(npuzzle ${SRC})

target_include_directories(npuzzle
    PUBLIC src/Log
    PUBLIC src/Parser
    PUBLIC src/UI
    PUBLIC build/_deps/piksel-src/src
)

target_link_libraries(npuzzle
    piksel
)
