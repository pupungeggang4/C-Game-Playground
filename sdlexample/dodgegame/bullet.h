#pragma once
#include "general.h"

typedef struct Vec2 Vec2;
typedef struct Rect2 Rect2;
typedef struct Player Player;
typedef struct Bullet {
    Rect2* rect;
    Vec2* velocity;
    float speed;
} Bullet;

Bullet* makeBullet();
void destroyBullet(Bullet**);
void moveBullet(Bullet*);
int checkPlayerCollide(Bullet*, Player*);

Bullet** makeBulletList(int size);
void destroyBulletList(Bullet***, int);
void insertBullet(Bullet**, int);
void renderBullet(Bullet**, int);
void handleBullet(Bullet**, int, Player*);
