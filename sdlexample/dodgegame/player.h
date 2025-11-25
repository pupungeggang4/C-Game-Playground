#pragma once
#include "general.h"

struct Rect;
typedef struct Rect Rect;

struct Player {
    float speed;
    Rect* rect;
};
typedef struct Player Player;

Player* makePlayer();
void destroyPlayer(Player**);
