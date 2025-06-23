#ifndef RANGER_H
#define RANGER_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entityes/entitiesTypes.h"
#include "graphics/texture.h"
#include "graphics/deltaTime.h"
#include "input/input.h"
#include "log/logger.h"

#define RANGER_WIDTH 50
#define RANGER_HEIGHT 50
#define RANGER_SCALE 2
#define RANGER_SPEED 500
#define RANGER_GRAVITY 8000.0f
#define RANGER_JUMP_FORCE -2400.0f 
#define RANGER_ANIMATION_SPEED 90

#define RANGER_IDLE_ANIMATION_FRAMES 12

typedef struct s_sprites_ranger {
    Uint16 base;
    Uint16 projectiles;
} SPRITES_RANGER;

typedef enum {
    R_IDLE,
    R_MOVING,
    R_JUMPING,
    R_HIT,
    R_DEAD
} RANGER_STATE;

typedef struct s_ranger {
    POSITION pos;
    SPRITES_RANGER sprites;
    RANGER_STATE state;
    
    TIME animationTime;
    Uint8 animationFrame;
    
    float velocityY;
    bool isOnGround;

} RANGER;

RANGER initRanger(void);
void initRangerSprites(RANGER *ranger);
void renderRanger(RANGER *ranger);
void moveRanger(RANGER *ranger);
void animateRanger(RANGER *ranger);

#endif