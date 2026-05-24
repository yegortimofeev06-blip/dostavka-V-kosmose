cmake_minimum_required(VERSION 3.10)
project(DostavkaVkosmose C)

set(CMAKE_C_STANDARD 11)

add_executable(game 
    igruha/main.c 
    igruha/game.c
)

target_include_directories(game PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/igruha"
    "C:/raylib/include"
)

target_link_directories(game PRIVATE 
    "C:/raylib/lib"
)

target_link_libraries(game 
    raylib 
    opengl32 
    gdi32 
    winmm
)