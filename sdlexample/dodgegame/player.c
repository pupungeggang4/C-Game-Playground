#include "player.h"
#include "var.h"
#include "shape.h"

Player* makePlayer() {
    Player* player = malloc(sizeof(Player));
    
    if (player == NULL) {
        printf("Failed to allocate player.\n");
        return NULL;
    }

    player->rect = makeRect2(400.0f, 300.0f, 80.0f, 80.0f);

    if (player->rect == NULL) {
        printf("Failed to allocate player rect.\n");
        return NULL;
    }

    player->speed = 320.0f;
    return player;
}

void destroyPlayer(Player** playerPtr) {
    if (playerPtr == NULL || *playerPtr == NULL) {
        return;
    }

    Player* player = *playerPtr;
    destroyRect2(&(player->rect));
    free(player);
    *playerPtr = NULL;
}

void movePlayer(Player* player) {
    if (player != NULL) {
        if (keyPressed[LEFT] == 1) {
            player->rect->pos->x -= player->speed * delta;
        }
        if (keyPressed[RIGHT] == 1) {
            player->rect->pos->x += player->speed * delta;
        }
        if (keyPressed[UP] == 1) {
            player->rect->pos->y -= player->speed * delta;
        }
        if (keyPressed[DOWN] == 1) {
            player->rect->pos->y += player->speed * delta;
        }
    }
}
