cmake_minimum_required(VERSION 3.13)

project(tictactoe)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        src/core/player.cpp src/core/player.h
        src/core/game.cpp src/core/game.h
        src/core/controller.h
        src/gui.cpp src/gui.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/arial.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(tictactoe ${SOURCE_FILES})

target_link_libraries(tictactoe -lsfml-graphics -lsfml-window -lsfml-system)