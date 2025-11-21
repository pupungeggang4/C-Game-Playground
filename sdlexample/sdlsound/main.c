#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int main (int argc, char** argv) {
    SDL_Window* window;
    window = SDL_CreateWindow("SDL2 Mixer Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL mixer.\n");
        return -1;
    }
    if ((Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG) != MIX_INIT_OGG) {
        printf("Failed to initialize OGG.\n");
        return -1;
    }
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("Failed to open audion.\n");
        return -1;
    }    
    Mix_Music *music;
    music = Mix_LoadMUS("sample.ogg");
    int running = 1;
    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Music play failed\n");
    }
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

    Mix_FreeMusic(music);
    music = NULL;
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}