#include "general.h"
#include "var.h"
#include "shape.h"
#include "player.h"

void handleScene();
void handleInput();

int main(int argc, char** argv) {
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

    player = makePlayer();
    destroyPlayer(player);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

void handleScene() {

}

void handleInput() {

}
