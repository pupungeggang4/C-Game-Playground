#include "player.h"
#include "shape.h"

Player* makePlayer() {
    Player* player = malloc(sizeof(Player));
    
    if (player == NULL) {
        printf("Failed to allocate player.\n");
        return NULL;
    }

    player->rect = malloc(sizeof(Rect));
    if (player->rect == NULL) {
        printf("Failed to allocate player rect.\n");
        return NULL;
    }

    player->rect = malloc(sizeof(Rect));
    player->rect->x = 400.0f;
    player->rect->y = 300.0f;
    player->rect->w = 80.0f;
    player->rect->h = 80.0f;
    player->speed = 320.0f;
    return player;
}

void destroyPlayer(Player** playerPtr) {
    if (playerPtr == NULL || *playerPtr == NULL) {
        return;
    }

    Player* player = *playerPtr;
    destroyRect(&player->rect);
    free(player);
    *playerPtr = NULL;
}
