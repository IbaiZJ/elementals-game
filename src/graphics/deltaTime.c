#include "deltaTime.h"

Uint32 lastFrameTime;
Uint32 fpsCounterStart;

float currentFPS;
int frameCount;

float deltaTime = 0.0f;

float getDeltaTime() {
    return deltaTime;
}

void initDeltaTime() {
    lastFrameTime = SDL_GetTicks();
    fpsCounterStart = SDL_GetTicks();
    
    currentFPS = 0.0f;
    frameCount = 0;
}

void calculateDeltaTime() {
    Uint32 currentFrameTime = SDL_GetTicks();
    char fpsText[16];
    
    deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentFrameTime;

    frameCount++;
    if (SDL_GetTicks() - fpsCounterStart >= 1000) {
        currentFPS = frameCount;
        frameCount = 0;
        fpsCounterStart = SDL_GetTicks();
    }
    snprintf(fpsText, sizeof(fpsText), "FPS: %.0f", currentFPS);
    renderText(10, 10, fpsText, (SDL_Color){255, 255, 255, 255});
}
