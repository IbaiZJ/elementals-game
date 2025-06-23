#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "log/logger.h"

#define GAME_NAME "ELEMENTALS"
#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080

SDL_Renderer* getRenderer(void);
int createWindow();
void destroyWindow();
int createRenderer();
void destroyRenderer();

#endif