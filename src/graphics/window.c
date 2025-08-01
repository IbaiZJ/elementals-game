#include "window.h"

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Renderer* getRenderer(void) {
    return renderer;
}

int createWindow() {
    window = SDL_CreateWindow(
        GAME_NAME, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        GAME_WIDTH, GAME_HEIGHT, 
        SDL_WINDOW_FULLSCREEN_DESKTOP
    );
    if(!window) {
        logMessage(LOG_ERROR, "SDL_CreateWindow failed. Unable to set window!: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

void destroyWindow() {
    SDL_DestroyWindow(window);
}

int createRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        logMessage(LOG_ERROR, "SDL_CreateRenderer failed: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

void destroyRenderer() {
    SDL_DestroyRenderer(renderer);
}