#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include "graphics/window.h"
#include "graphics/deltaTime.h"
#include "input/input.h"
#include "ttf/text.h"
#include "entities/heroes/ranger.h"
#include "log/logger.h"
#include "map/map.h"

int initAll();
void destroyAll();
void gameLoop();

#endif