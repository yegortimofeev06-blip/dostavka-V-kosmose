#pragma once
#include "raylib.h"

typedef enum { MENU, GAMEPLAY, GAMEOVER } State;

typedef struct {
    float angle;
    float speed;
    float radius;
    Vector2 pos;
} Korabl;

typedef struct {
    float angle;
    Vector2 pos;
} Cel;

typedef struct {
    float angle;
    float speed;
    Vector2 pos;
} Meteor;

typedef struct {
    State sostoyanie;
    Korabl korabl;
    Cel cel;
    Meteor meteor;
    Vector2 center;
    int schot;
} Game;

void GameInit(Game *g);
void GameUpdate(Game *g);
void GameDraw(Game *g);
