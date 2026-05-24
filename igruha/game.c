#include "game.h"
#include <math.h>
#include <stdlib.h>

#define RADIUS_ORBITY   160.0f
#define SKOROST_KORABLA   1.8f
#define SKOROST_METEORA   1.1f
#define RADIUS_KORABLA   12.0f
#define RADIUS_CELI      10.0f
#define RADIUS_METEORA   14.0f
#define RADIUS_PLANETY   40.0f

static float SluchaynyUgol() {
    return (float)(rand() % 628) / 100.0f;
}

static Vector2 UgolVPoziciyu(Vector2 center, float radius, float ugol) {
    Vector2 p;
    p.x = center.x + radius * cosf(ugol);
    p.y = center.y + radius * sinf(ugol);
    return p;
}

void GameInit(Game *g) {
    g->sostoyanie  = MENU;
    g->schot       = 0;
    g->center.x    = GetScreenWidth()  / 2.0f;
    g->center.y    = GetScreenHeight() / 2.0f;

    g->korabl.angle  = 0.0f;
    g->korabl.speed  = SKOROST_KORABLA;
    g->korabl.radius = RADIUS_ORBITY;
    g->korabl.pos    = UgolVPoziciyu(g->center, RADIUS_ORBITY, 0.0f);

    g->cel.angle = SluchaynyUgol();
    g->cel.pos   = UgolVPoziciyu(g->center, RADIUS_ORBITY, g->cel.angle);

    g->meteor.angle = SluchaynyUgol();
    g->meteor.speed = SKOROST_METEORA;
    g->meteor.pos   = UgolVPoziciyu(g->center, RADIUS_ORBITY, g->meteor.angle);
}

void GameUpdate(Game *g) {
    float dt = GetFrameTime();

    if (g->sostoyanie == MENU) {
        if (IsKeyPressed(KEY_SPACE)) g->sostoyanie = GAMEPLAY;
        return;
    }

    if (g->sostoyanie == GAMEOVER) {
        if (IsKeyPressed(KEY_SPACE)) GameInit(g);
        return;
    }

    if (IsKeyPressed(KEY_SPACE))
        g->korabl.speed = -g->korabl.speed;

    g->korabl.angle += g->korabl.speed * dt;
    g->meteor.angle -= g->meteor.speed * dt;

    g->korabl.pos = UgolVPoziciyu(g->center, RADIUS_ORBITY, g->korabl.angle);
    g->meteor.pos = UgolVPoziciyu(g->center, RADIUS_ORBITY, g->meteor.angle);

    if (CheckCollisionCircles(g->korabl.pos, RADIUS_KORABLA, g->cel.pos, RADIUS_CELI)) {
        g->schot++;
        g->cel.angle = g->korabl.angle + 1.5f + SluchaynyUgol() * 0.5f;
        g->cel.pos   = UgolVPoziciyu(g->center, RADIUS_ORBITY, g->cel.angle);
    }

    if (CheckCollisionCircles(g->korabl.pos, RADIUS_KORABLA, g->meteor.pos, RADIUS_METEORA))
        g->sostoyanie = GAMEOVER;
}

void GameDraw(Game *g) {
    float napravlenie, cx, cy;
    Vector2 nos, levo, pravo;
    const char *msg;
    int i;

    BeginDrawing();
    ClearBackground((Color){ 8, 8, 20, 255 });

    DrawCircleLines((int)g->center.x, (int)g->center.y,
                    RADIUS_ORBITY, (Color){ 60, 60, 90, 255 });
    DrawCircleV(g->center, RADIUS_PLANETY, (Color){ 70, 130, 180, 255 });

    if (g->sostoyanie == MENU) {
        DrawText("Dostavka V kosmose",
                 GetScreenWidth() / 2 - MeasureText("Dostavka V kosmose", 28) / 2,
                 GetScreenHeight() / 2 - 60, 28, WHITE);
        DrawText("SPACE - start",
                 GetScreenWidth() / 2 - MeasureText("SPACE - start", 20) / 2,
                 GetScreenHeight() / 2, 20, RED);
        EndDrawing();
        return;
    }

    for (i = 0; i < 5; i++) {
        float a1 = (float)i * 2.0f * 3.14159f / 5.0f - 3.14159f / 2.0f;
        float a2 = a1 + 3.14159f / 5.0f;
        float a3 = a1 + 2.0f * 3.14159f / 5.0f;
        Vector2 p1 = { g->cel.pos.x + cosf(a1) * RADIUS_CELI,         g->cel.pos.y + sinf(a1) * RADIUS_CELI };
        Vector2 p2 = { g->cel.pos.x + cosf(a2) * RADIUS_CELI * 0.45f, g->cel.pos.y + sinf(a2) * RADIUS_CELI * 0.45f };
        Vector2 p3 = { g->cel.pos.x + cosf(a3) * RADIUS_CELI,         g->cel.pos.y + sinf(a3) * RADIUS_CELI };
        DrawTriangle(p1, p2, p3, YELLOW);
    }

    DrawCircleV(g->meteor.pos, RADIUS_METEORA * 1.5f, (Color){ 180, 80, 40, 255 });

    napravlenie = g->korabl.angle + (g->korabl.speed > 0 ? 1.5708f : -1.5708f);
    cx = g->korabl.pos.x;
    cy = g->korabl.pos.y;
    nos.x   = cx + cosf(napravlenie) * RADIUS_KORABLA;
    nos.y   = cy + sinf(napravlenie) * RADIUS_KORABLA;
    levo.x  = cx + cosf(napravlenie + 2.5f) * RADIUS_KORABLA * 0.7f;
    levo.y  = cy + sinf(napravlenie + 2.5f) * RADIUS_KORABLA * 0.7f;
    pravo.x = cx + cosf(napravlenie - 2.5f) * RADIUS_KORABLA * 0.7f;
    pravo.y = cy + sinf(napravlenie - 2.5f) * RADIUS_KORABLA * 0.7f;
    DrawTriangle(nos, pravo, levo, WHITE);

    DrawText(TextFormat("Schot: %d", g->schot), 12, 12, 22, WHITE);

    if (g->sostoyanie == GAMEOVER) {
        msg = "GAME OVER - SPACE to restart";
        DrawText(msg,
                 GetScreenWidth() / 2 - MeasureText(msg, 24) / 2,
                 GetScreenHeight() / 2 - 12, 24, RED);
    }

    EndDrawing();
}