
cmake_minimum_required(VERSION 3.13)
project(npuzzle)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(SFML 2.4 COMPONENTS graphics audio REQUIRED)
execute_process(COMMAND cp ../data/CaviarDreams.ttf .)

set(SRC src/main.cc
        src/Log/log.cc
        src/UI/UI.cc
        src/Parser/Parser.cc
        
        src/Algo/NPuzzleSolver.cc
        src/Algo/State.cc)

add_executable(npuzzle ${SRC})

target_include_directories(npuzzle
    PUBLIC src/Log
    PUBLIC src/Parser
    PUBLIC src/Algo
    PUBLIC src/UI
    PUBLIC src/Common
)

target_link_libraries(npuzzle sfml-graphics sfml-audio)
