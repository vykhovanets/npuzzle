
cmake_minimum_required(VERSION 3.13)
project(npuzzle)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SRC src/main.cc
        src/Log/log.cc
        src/UI/UI.cc
        src/Parser/Parser.cc)

add_executable(npuzzle ${SRC})

target_include_directories(npuzzle
    PUBLIC src/Log
    PUBLIC src/Parser
    PUBLIC src/UI
)

target_link_libraries(npuzzle sfml-graphics sfml-audio)
