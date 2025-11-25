#pragma once
#include "general.h"

typedef struct Rect2 Rect2;

typedef struct Player {
    float speed;
    Rect2* rect;
} Player;

Player* makePlayer();
void destroyPlayer(Player**);
void movePlayer(Player*);
