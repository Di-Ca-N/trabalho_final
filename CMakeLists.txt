cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_COMPILER "gcc")

project("Trabalho Final")

add_subdirectory(libs/raylib)

add_executable(main 
    src/main.c
    src/game.c
    src/saves.c
    src/maps.c
    src/graphics.c
    src/ranking.c
)

target_link_libraries(main raylib)
