#ifndef RANGER_H
#define RANGER_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entities/entitiesTypes.h"
#include "graphics/texture.h"
#include "graphics/deltaTime.h"
#include "input/input.h"
#include "log/logger.h"
#include "map/map.h"

typedef struct s_sprites_ranger {
    Uint16 base;
    Uint16 projectiles;
} SPRITES_RANGER;

typedef enum {
    R_IDLE,
    R_MOVING,
    R_JUMPING,

    R_ROLL,
    R_SLIDE,

    R_HIT,
    R_DEAD
} RANGER_STATE;

typedef struct s_ranger {
    POSITION pos;
    SPRITES_RANGER sprites;
    RANGER_STATE state;
    HORIZONTAL_POSITION horizontalPosition;
    
    TIME animationTime;
    Uint8 animationFrame;
    
    float velocityY;
    bool isOnGround;

} RANGER;

RANGER initRanger(void);
void initRangerSprites(RANGER *ranger);
void renderRanger(RANGER *ranger);
void moveRanger(RANGER* ranger);
void updateRangerState(RANGER *ranger);
void animateRanger(RANGER *ranger);
Uint8 getRangerStateMaxFrames(RANGER *ranger);
Uint16 getRangerStateAnimationSpeed(RANGER *ranger);
void toggleRangerState(RANGER *ranger, RANGER_STATE newState);
Uint8 getSpriteAnimationRow(RANGER *ranger);
char* getStateName(RANGER_STATE state);

#endif