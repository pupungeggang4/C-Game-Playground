#pragma once
#include <math.h>

struct Point {
    float x;
    float y;
};
typedef struct Point Point;

float distance(Point, Point);
