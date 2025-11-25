#include "general.h"
#include "var.h"
#include "shape.h"
#include "player.h"
#include "bullet.h"

void loop();
void handleInput();
void handleScene();
void render();

int main(int argc, char** argv) {
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL video.\n");
        return -1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Failed to initialize PNG image.\n");
        return -1;
    }
    if (TTF_Init() == -1) {
        printf("Failed to load ttf.\n");
        return -1;
    }
    font = TTF_OpenFont("font/neodgm.ttf", 32);
    if (!font) {
        printf("Failed to load font.\n");
        return -1;
    }

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Dodge Game");
    SDL_RenderSetVSync(renderer, 1);

    player = makePlayer();
    bulletList = makeBulletList(MAX_BULLET_LIMIT);

    framePrevious = SDL_GetTicks() / 1000.0f;
    while (running) {
        loop();
    }

    destroyPlayer(&player);
    destroyBulletList(&bulletList, MAX_BULLET_LIMIT);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

void loop() {
    frameCurrent = SDL_GetTicks() / 1000.0f;
    delta = frameCurrent - framePrevious;
    framePrevious = SDL_GetTicks() / 1000.f;
    handleInput();
    handleScene();
    render();
}

void handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        }

        if (event.type == SDL_KEYDOWN) {
            SDL_Scancode key = event.key.keysym.scancode;
            if (key == SDL_SCANCODE_UP) {
                keyPressed[UP] = 1;
            }
            if (key == SDL_SCANCODE_DOWN) {
                keyPressed[DOWN] = 1;
            }
            if (key == SDL_SCANCODE_LEFT) {
                keyPressed[LEFT] = 1;
            }
            if (key == SDL_SCANCODE_RIGHT) {
                keyPressed[RIGHT] = 1;
            }
            if (gameOver == 1) {
                gameOver = 0;
                timeElapsed = 0.0f;
                score = 0;
                destroyPlayer(&player);
                destroyBulletList(&bulletList, MAX_BULLET_LIMIT);
                player = makePlayer();
                bulletList = makeBulletList(MAX_BULLET_LIMIT);
            }
        }

        if (event.type == SDL_KEYUP) {
            SDL_Scancode key = event.key.keysym.scancode;
            if (key == SDL_SCANCODE_UP) {
                keyPressed[UP] = 0;
            }
            if (key == SDL_SCANCODE_DOWN) {
                keyPressed[DOWN] = 0;
            }
            if (key == SDL_SCANCODE_LEFT) {
                keyPressed[LEFT] = 0;
            }
            if (key == SDL_SCANCODE_RIGHT) {
                keyPressed[RIGHT] = 0;
            }
        }
    }
}

void handleScene() {
    if (gameOver == 0) {
        timeElapsed += delta;
        score = timeElapsed;
        movePlayer(player);
        if (bulletLeftTime <= 0) {
            bulletLeftTime = bulletInterval;
            insertBullet(bulletList, MAX_BULLET_LIMIT);
        } else {
            bulletLeftTime -= delta;
        }
        handleBullet(bulletList, MAX_BULLET_LIMIT, player);
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_Rect rect = {player->rect->pos->x - player->rect->size->x / 2.0f, player->rect->pos->y - player->rect->size->y / 2.0f, player->rect->size->x, player->rect->size->y};
    SDL_RenderFillRect(renderer, &rect);
    renderBullet(bulletList, MAX_BULLET_LIMIT);

    SDL_Surface* textSurface;
    SDL_Color color = {255, 255, 0, 255};
    sprintf(scoreStr, "Score: %d", score);
    if (gameOver == 0) {
        textSurface = TTF_RenderText_Blended(font, scoreStr, color);
    } else {
        textSurface = TTF_RenderText_Blended(font, "Game Over!", color);
    }
    if (textSurface != NULL) {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture != NULL) {
            SDL_Rect dstRect = {20, 20, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
    SDL_FreeSurface(textSurface);

    SDL_RenderPresent(renderer);
}
