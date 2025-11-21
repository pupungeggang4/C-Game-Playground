#include <SDL3/SDL.h>
#include <GL/gl.h>

#include <stdio.h>

SDL_Window* window;

int main(int argc, char** argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("Failed to initialize SDL Video.");
        return -1;
    }
    window = SDL_CreateWindow("SDL3 OpenGL Triangle", 800, 600, SDL_WINDOW_OPENGL);

    if (!window) {
        printf("Failed to create window.");
        return -1;
    }

    float scale = SDL_GetWindowDisplayScale(window);
    SDL_SetWindowSize(window, 800 * scale, 600 * scale);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_GL_CreateContext(window);
    glViewport(0, 0, 800 * scale, 600 * scale);

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.0, 0.5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.5, -0.5);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(0.5, -0.5);
        glEnd();
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}