#include "bullet.h"
#include "var.h"
#include "shape.h"
#include "player.h"

Bullet* makeBullet() {
    Bullet* bullet = malloc(sizeof(Bullet));
    if (bullet == NULL) {
        return NULL;
    }

    bullet->rect = makeRect2(0.0f, 0.0f, 40.0f, 40.0f);
    if (bullet->rect == NULL) {
        free(bullet);
        return NULL;
    }
    bullet->velocity = malloc(sizeof(Vec2));
    if (bullet->velocity == NULL) {
        destroyRect2(&(bullet->rect));
        free(bullet);
        return NULL;
    }
    bullet->velocity->x = 0.0f;
    bullet->velocity->y = 0.0f;
    return bullet;
}

void destroyBullet(Bullet** bulletPtr) {
    if (bulletPtr == NULL || *bulletPtr == NULL) {
        return;
    }

    Bullet* bullet = *bulletPtr;

    if (bullet->velocity != NULL) {
        free(bullet->velocity);
        bullet->velocity = NULL;
    }

    if (bullet->rect != NULL) {
        destroyRect2(&(bullet->rect));
        bullet->rect = NULL;
    }

    free(bullet);
    *bulletPtr = NULL;
}

void moveBullet(Bullet* bullet) {
    if (bullet != NULL) {
        bullet->rect->pos->x += bullet->velocity->x * delta;
        bullet->rect->pos->y += bullet->velocity->y * delta;
    }
}

int checkPlayerCollide(Bullet* bullet, Player* player) {
    if (bullet != NULL && player != NULL) {
        if (distance(*(bullet->rect->pos), *(player->rect->pos)) < bullet->rect->size->x / 2.0f + player->rect->size->x / 2.0f) {
            return 1;
        }
    }
    return 0;
}

Bullet** makeBulletList(int size) {
    Bullet** bulletList = malloc(size * sizeof(Bullet*));

    if (bulletList == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        bulletList[i] = NULL;
    }
    return bulletList;
}

void destroyBulletList(Bullet*** bulletPtr, int size) {
    if (bulletPtr == NULL || *bulletPtr == NULL) {
        return;
    }

    Bullet** bullet = *bulletPtr;

    for (int i = 0; i < size; i++) {
        if (bullet[i] != NULL) {
            destroyBullet(&bullet[i]);
        }
    }

    free(bullet);
    *bulletPtr = NULL;
}

void insertBullet(Bullet** bulletList, int size) {
    Bullet* bullet = makeBullet();
    if (bullet == NULL) {
        return;
    }

    int spawnPos = rand() % 4;
    if (spawnPos == 0 || spawnPos == 2) {
        bullet->velocity->y = 0;
        bullet->rect->pos->y = rand() % 560 + 20.0f;
        if (spawnPos == 0) {
            bullet->rect->pos->x = -20.0f;
            bullet->velocity->x = 200.0f;
        } else {
            bullet->rect->pos->x = 820.0f;
            bullet->velocity->x = -200.0f;
        }
    } else if (spawnPos == 1 || spawnPos == 3) {
        bullet->velocity->x = 0;
        bullet->rect->pos->x = rand() % 760 + 20.0f;
        if (spawnPos == 1) {
            bullet->rect->pos->y = -20.0f;
            bullet->velocity->y = 200.0f;
        } else {
            bullet->rect->pos->y = 620.0f;
            bullet->velocity->y = -200.0f;
        }
    }

    int inserted = 0;

    for (int i = 0; i < size; i++) {
        if (bulletList[i] == NULL) {
            bulletList[i] = bullet;
            inserted = 1;
            break;
        }
    }

    if (!inserted) {
        destroyBullet(&bullet);
    }
}

void handleBullet(Bullet** bulletList, int size, Player* player) {
    for (int i = 0; i < size; i++) {
        if (bulletList[i] != NULL && player != NULL) {
            Bullet* bullet = bulletList[i];
            moveBullet(bullet);
            if (checkPlayerCollide(bullet, player)) {
                gameOver = 1;
            }
            else if (bullet->rect->pos->x < -80.0f || bullet->rect->pos->x > 880.0f || bullet->rect->pos->y < -80.0f || bullet->rect->pos->y > 680.0f) {
                destroyBullet(&bulletList[i]);
            }
        }
    }
}

void renderBullet(Bullet** bulletList, int size) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if (bulletList != NULL) {
        for (int i = 0; i < size; i++) {
            if (bulletList[i] != NULL) {
                Bullet* bullet = bulletList[i];
                SDL_Rect rect = {bullet->rect->pos->x - bullet->rect->size->x / 2.0f, bullet->rect->pos->y - bullet->rect->size->y / 2.0f, bullet->rect->size->x, bullet->rect->size->y};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
