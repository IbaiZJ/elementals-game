#ifndef RANGER_H
#define RANGER_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "entityes/entitiesTypes.h"
#include "graphics/texture.h"
#include "graphics/deltaTime.h"
#include "input/input.h"

#define RANGER_SPRITES_PATH "assets/img/ranger/"

#define RANGER_WIDTH 50
#define RANGER_HEIGHT 50
#define RANGER_SCALE 2
#define RANGER_SPEED 500

#define RANGER_IDLE_SPRITES_COUNT 12

typedef struct s_sprites_ranger {
    int idle[RANGER_IDLE_SPRITES_COUNT];
} SPRITES_RANGER;

typedef struct s_ranger {
    POSITION pos;
    SPRITES_RANGER sprites;
} RANGER;

RANGER initRanger(void);
void initRangerSprites(RANGER *ranger);
void renderRanger(RANGER *ranger);
void moveRanger(RANGER *ranger);

#endif