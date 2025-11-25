#pragma once
#include "general.h"

typedef struct Bullet Bullet;
typedef struct Player Player;

extern const int UP, DOWN, LEFT, RIGHT;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;
extern float frameCurrent;
extern float framePrevious;
extern float delta;
extern int running;
extern int keyPressed[4];

extern float timeElapsed;
extern int score;
extern char scoreStr[100];
extern Player* player;
extern Bullet** bulletList;
extern float bulletLeftTime;
extern float bulletInterval;
extern int gameOver;
