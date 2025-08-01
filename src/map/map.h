#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphics/texture.h"
#include "graphics/window.h"
#include "log/logger.h"

#define TILE_SIZE 60

typedef enum {
    TT_VOID,
    TT_GROUND,
    TT_PLATFORM
} TILE;

typedef struct {
    int width;
    int height;
    int** tiles;
} MAP;

MAP initMap();
void freeMap(MAP* map);
void renderMap(MAP* map);

#endif
