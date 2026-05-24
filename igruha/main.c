#include "raylib.h"
#include "game.h"

static Game game;

static void Loop(void) {
    GameUpdate(&game);
    GameDraw(&game);
}

int main(void) {
    InitWindow(800, 600, "Orbital Delivery");
    SetTargetFPS(60);

    GameInit(&game);

    while (!WindowShouldClose()) {
        Loop();
    }

    CloseWindow();
    return 0;
}
