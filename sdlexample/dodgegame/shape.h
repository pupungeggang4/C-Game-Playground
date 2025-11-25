#pragma once
#include "general.h"

typedef struct Vec2 {
    float x;
    float y;
} Vec2;

typedef struct Rect2 {
    Vec2* pos;
    Vec2* size;
} Rect2;

Vec2 makeVec2(float, float);
Rect2* makeRect2(float, float, float, float);
void destroyRect2(Rect2**);
float distance(Vec2, Vec2);
