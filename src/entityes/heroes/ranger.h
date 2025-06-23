#ifndef RANGER_H
#define RANGER_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "entityes/entitiesTypes.h"
#include "graphics/texture.h"

#define RANGER_SPRITES_PATH "assets/sprites/ranger/"

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


#endif