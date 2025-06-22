#include "game.h"

extern SDL_Renderer* renderer;

int initAll() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return -1;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return -1;
    }
    if(TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }
    if(createWindow() < 0) {
        printf("SDL could not create window!");
        return -1;
    }
    if(createRenderer() < 0) {
        printf("SDL could not create renderer!");
        return -1;
    }
    if(initText() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }
    initDeltaTime();
    // initAudio();

    return 1;
}

void destroyAll() {
    destroyRenderer();
    destroyWindow();
    // Mix_CloseAudio();
    SDL_Quit();
}

void gameLoop() {
    Uint8 quit = 0;

    while (!quit) {
        SDL_RenderClear(renderer);        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        
        pollEvents();
        exitEvent(&quit);
        calculateDeltaTime();
        

        SDL_RenderPresent(renderer);
    }

}