#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "log/logger.h"
#include "graphics/window.h"

int initText(void);
void destroyText(void);
void renderText(int x, int y, char *text, SDL_Color color);


#endif