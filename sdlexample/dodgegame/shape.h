#pragma once
#include "general.h"

struct Vec2 {
    float x;
    float y;
};
typedef struct Vec2 Vec2;

struct Rect2 {
    Vec2 pos;
    Vec2 size;
};
typedef struct Rect2 Rect2;

Vec2 makeVec2(float, float);
Rect2* makeRect2(float, float, float, float);
void destroyRect2(Rect2**);
float distance(Vec2, Vec2);
