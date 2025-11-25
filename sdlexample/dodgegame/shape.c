#include "shape.h"

Vec2 makeVec2(float x, float y) {
    Vec2 v = {x, y};
    return v;
}

Rect2* makeRect2(float x, float y, float w, float h) {
    Rect2* rect = malloc(sizeof(Rect2));
    if (rect == NULL) {
        return NULL;
    }

    Vec2* pos = malloc(sizeof(Vec2));
    Vec2* size = malloc(sizeof(Vec2));

    if (pos == NULL) {
        free(rect);
        return NULL;
    }

    if (size == NULL) {
        free(rect);
        free(pos);
        return NULL;
    }

    rect->pos = pos;
    rect->size = size;
    rect->pos->x = x;
    rect->pos->y = y;
    rect->size->x = w;
    rect->size->y = h;
    return rect;
}

void destroyRect2(Rect2** rectPtr) {
    if (rectPtr == NULL || *rectPtr == NULL) {
        return;
    }

    Rect2* rect = *rectPtr;
    if (rect->pos != NULL) {
        free(rect->pos);
        rect->pos = NULL;
    }
    if (rect->size != NULL) {
        free(rect->size);
        rect->size = NULL;
    }
    if (rect != NULL) {
        free(rect);
    }

    *rectPtr = NULL;
}

float distance(Vec2 v1, Vec2 v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}
