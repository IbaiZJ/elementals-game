#include "game.h"

extern SDL_Renderer* renderer;

int initAll() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logMessage(LOG_ERROR, "SDL_Init (VIDEO) failed: %s", SDL_GetError());
        return -1;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        logMessage(LOG_ERROR, "SDL_Init (AUDIO) failed: %s", SDL_GetError());
        return -1;
    }
    if (TTF_Init() < 0) {
        logMessage(LOG_ERROR, "TTF_Init failed: %s", TTF_GetError());
        return -1;
    }
    if (createWindow() < 0) {
        logMessage(LOG_ERROR, "Failed to create window");
        return -1;
    }
    if (createRenderer() < 0) {
        logMessage(LOG_ERROR, "Failed to create renderer");
        return -1;
    }
    if (initText() < 0) {
        logMessage(LOG_ERROR, "initText failed: %s", TTF_GetError());
        return -1;
    }

    initDeltaTime();
    // initAudio();

    if (initInputs() < 0) {
        logMessage(LOG_ERROR, "Failed to initialize inputs");
        return -1;
    }

    logMessage(LOG_INFO, "All systems initialized correctly");

    return 1;
}

void destroyAll() {
    logMessage(LOG_INFO, "Shutting down...");
    destroyRenderer();
    destroyWindow();
    // Mix_CloseAudio();
    SDL_Quit();
}

void gameLoop() {
    Uint8 quit = 0;

    MAP map = initMap();
    if(map.tiles == NULL) {
        logMessage(LOG_ERROR, "Failed to initialize map");
        return;
    }

    RANGER ranger = initRanger();

    logMessage(LOG_INFO, "Entering game loop");
    while (!quit) {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        pollEvents();
        exitEvent(&quit);
        calculateDeltaTime();

        moveRanger(&ranger, map);
        animateRanger(&ranger);

        renderMap(&map);
        renderRanger(&ranger);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(renderer);
    }

    logMessage(LOG_INFO, "Exited game loop");
}
