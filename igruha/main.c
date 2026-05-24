#include "raylib.h"
#include "game.h"

static Game game;

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    
    void Loop(void) {
        GameUpdate(&game);
        GameDraw(&game);
    }
#else
    static void Loop(void) {
        GameUpdate(&game);
        GameDraw(&game);
    }
#endif

int main(void) {
    InitWindow(800, 600, "Orbital Delivery");
    SetTargetFPS(60);

    GameInit(&game);

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(Loop, 0, 1);
    #else
        while (!WindowShouldClose()) {
            Loop();
        }
    #endif

    CloseWindow();
    return 0;
}