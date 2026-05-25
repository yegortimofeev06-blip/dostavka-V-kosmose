cmake_minimum_required(VERSION 3.16)
project(DostavkaVkosmose C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
    igruha/main.c
    igruha/game.c
)

target_include_directories(${PROJECT_NAME} PRIVATE "C:/raylib/include")
target_link_directories(${PROJECT_NAME} PRIVATE "C:/raylib/lib")
target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)