#include "var.h"
#include "player.h"

const int LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
float frameCurrent = 0.0f;
float framePrevious = 0.0f;
float delta = 0.0f;
int running = 1;
int keyPressed[4] = {0, 0, 0, 0};

float timeElapsed = 0.0f;
int score = 0;
char scoreStr[100] = "";
Player* player = NULL;
Bullet** bulletList = NULL;
float bulletLeftTime = 0.5f;
float bulletInterval = 0.5f;
int gameOver = 0;
