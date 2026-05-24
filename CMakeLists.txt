cmake_minimum_required(VERSION 3.10)
project(DostavkaVkosmose C)

set(CMAKE_C_STANDARD 11)

find_package(raylib REQUIRED)

add_executable(game 
    igruha/main.c 
    igruha/game.c
)

target_include_directories(game PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/igruha"
)

target_link_libraries(game raylib)

if(EMSCRIPTEN)
    set_target_properties(game PROPERTIES SUFFIX ".html")
    target_link_options(game PRIVATE 
        "SHELL:-s WASM=1"
        "SHELL:-s USE_GLFW=3"
        "SHELL:-s ALLOW_MEMORY_GROWTH=1"
        "SHELL:-s INITIAL_MEMORY=67108864"
        "SHELL:--shell-file=${CMAKE_CURRENT_SOURCE_DIR}/shell.html"
    )
endif()