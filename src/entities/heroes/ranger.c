#include "ranger.h"

// #define RANGER_WIDTH = 50;
// #define RANGER_HEIGHT = 50;
#define RANGER_SCALE 2
#define RANGER_SPEED 400

#define RANGER_WIDTH 50
#define RANGER_HEIGHT 50
#define RANGER_SPRITE_WIDTH 288
#define RANGER_SPRITE_HEIGHT 128

#define RANGER_GRAVITY 8000.0f
#define RANGER_JUMP_FORCE -2400.0f

#define RANGER_IDLE_ANIMATION_FRAMES 12
#define RANGER_IDLE_ANIMATION_SPEED 120
#define RANGER_MOVING_ANIMATION_FRAMES 10
#define RANGER_MOVING_ANIMATION_SPEED 70
#define RANGER_JUMPING_ANIMATION_FRAMES 3
#define RANGER_JUMPING_ANIMATION_SPEED 70
#define RANGER_ROLL_ANIMATION_FRAMES 8
#define RANGER_ROLL_ANIMATION_SPEED 100


RANGER initRanger(void) {
    RANGER ranger;

    ranger.pos.x = 100;
    ranger.pos.y = 100;
    initRangerSprites(&ranger);
    ranger.state = R_IDLE;
    ranger.horizontalPosition = HORIZONTAL_RIGHT;
    ranger.animationTime.start = SDL_GetTicks();
    ranger.animationFrame = 0;
    ranger.isOnGround = true;
    ranger.velocityY = 0.0f;

    return ranger;
}

void initRangerSprites(RANGER *ranger) {
    ranger->sprites.base = loadTexture("assets/img/ranger/ranger_288x128_SpriteSheet.png");
    scaleImage(ranger->sprites.base, 
        RANGER_SPRITE_WIDTH * RANGER_SCALE, RANGER_SPRITE_HEIGHT * RANGER_SCALE);

    logMessage(LOG_INFO, "Ranger sprites initialized");
}

void renderRanger(RANGER *ranger) {
    SDL_Renderer *renderer = getRenderer();

    /* renderTextureFramesGetFlipHorizontal(ranger->sprites.base, 
        (int[]){ ranger->animationFrame, getSpriteAnimationRow(ranger) }, 
        288, 128, ranger->horizontalPosition); */
    renderTextureFramesGetFlipHorizontal(ranger->sprites.base, 
        (int[]){ 0, 0 }, 
        288, 128, ranger->horizontalPosition);
    
    
    SDL_Rect rangerRect;
    rangerRect.x = ranger->pos.x;
    rangerRect.y = ranger->pos.y;
    rangerRect.w = 288 * RANGER_SCALE;
    rangerRect.h = 128 * RANGER_SCALE;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rangerRect);
    rangerRect.x -= 200;
    rangerRect.y += 128 * RANGER_SCALE;
    rangerRect.h = 1;
    rangerRect.w = 1000;
    SDL_RenderDrawRect(renderer, &rangerRect);
    rangerRect.x = ranger->pos.x + 288 - 55;
    rangerRect.y = ranger->pos.y + 128 * 2 - 110;
    rangerRect.w = 110;
    rangerRect.h = 110;
    SDL_RenderDrawRect(renderer, &rangerRect);

    /*char arr[32];
    snprintf(arr, sizeof(arr), "VelocityY: %.0f", ranger->velocityY);
    renderText(10, 50, arr, (SDL_Color){255, 255, 255, 255});
    renderText(10, 70, getStateName(ranger->state), (SDL_Color){255, 255, 255, 255});*/
}

void moveRanger(RANGER *ranger, MAP map) {
    INPUTS* input = getInput();
    float dt = getDeltaTime();

    // Gravity
    if(input->jump && ranger->isOnGround) {
        ranger->velocityY = RANGER_JUMP_FORCE;
        ranger->isOnGround = false;
        // toggleRangerState(ranger, R_JUMPING);
    }

    ranger->velocityY += RANGER_GRAVITY * dt;
    ranger->pos.y += ranger->velocityY * dt;

    if (ranger->pos.y >= 500.0f) {
        ranger->pos.y = 500.0f;
        ranger->velocityY = 0;
        ranger->isOnGround = true;
    }

    if(input->left) {
        ranger->pos.x -= RANGER_SPEED * dt;
        ranger->horizontalPosition = HORIZONTAL_LEFT;
        if (ranger->isOnGround) toggleRangerState(ranger, R_MOVING);
    }
    if(input->right) {
        ranger->pos.x += RANGER_SPEED * dt;
        ranger->horizontalPosition = HORIZONTAL_RIGHT;
        if (ranger->isOnGround) toggleRangerState(ranger, R_MOVING);
    }
    if(!input->left && !input->right && ranger->isOnGround) {
        toggleRangerState(ranger, R_IDLE);
    }

    moveImage(ranger->sprites.base, ranger->pos.x, ranger->pos.y);
}

/*
void moveRanger(RANGER* ranger, MAP* map) {
    INPUTS* input = getInput();
    float dt = getDeltaTime();

    // Salto
    if (input->jump && ranger->isOnGround) {
        ranger->velocityY = RANGER_JUMP_FORCE;
        ranger->isOnGround = false;
        toggleRangerState(ranger, R_JUMPING);
    }

    // Gravedad
    ranger->velocityY += RANGER_GRAVITY * dt;
    ranger->pos.y += ranger->velocityY * dt;

    // Colisión vertical con el suelo del mapa
    int tileX = (int)(ranger->pos.x / TILE_SIZE);
    int tileYBelow = (int)((ranger->pos.y + 128) / TILE_SIZE);

    if (tileYBelow < map->height && tileX >= 0 && tileX < map->width) {
        int belowTile = map->tiles[tileYBelow][tileX];
        if (belowTile == TT_PLATFORM || belowTile == TT_GROUND) {
            ranger->pos.y = tileYBelow * TILE_SIZE - 128;
            ranger->velocityY = 0;
            ranger->isOnGround = true;
        } else {
            ranger->isOnGround = false;
        }
    }

    // Movimiento horizontal
    if (input->left) {
        ranger->pos.x -= RANGER_SPEED * dt;
        ranger->horizontalPosition = HORIZONTAL_LEFT;
        if (ranger->isOnGround) toggleRangerState(ranger, R_MOVING);
    }
    if (input->right) {
        ranger->pos.x += RANGER_SPEED * dt;
        ranger->horizontalPosition = HORIZONTAL_RIGHT;
        if (ranger->isOnGround) toggleRangerState(ranger, R_MOVING);
    }

    // Idle si no se mueve
    if (!input->left && !input->right && ranger->isOnGround) {
        toggleRangerState(ranger, R_IDLE);
    }

    moveImage(ranger->sprites.base, ranger->pos.x, ranger->pos.y);
}
*/

/*void updateRangerState(RANGER *ranger) {
    INPUTS* input = getInput();

    if()
}*/

void animateRanger(RANGER *ranger) {
    ranger->animationTime.finish = SDL_GetTicks();
    if(ranger->animationTime.finish - ranger->animationTime.start > getRangerStateAnimationSpeed(ranger)) {
        ranger->animationTime.start += getRangerStateAnimationSpeed(ranger);
        if(ranger->animationFrame < getRangerStateMaxFrames(ranger) - 1) {
            ranger->animationFrame++;
        }
        else ranger->animationFrame = 0;
    }
}

Uint8 getRangerStateMaxFrames(RANGER *ranger) {
    switch(ranger->state) {
        case R_IDLE:
            return RANGER_IDLE_ANIMATION_FRAMES;
        case R_MOVING:
            return RANGER_MOVING_ANIMATION_FRAMES;
        case R_JUMPING:
            return RANGER_JUMPING_ANIMATION_FRAMES;
        case R_ROLL:
            return RANGER_ROLL_ANIMATION_FRAMES;
        case R_SLIDE:
        case R_HIT:
        case R_DEAD:
        default:
            return 0;
    }
}

Uint16 getRangerStateAnimationSpeed(RANGER *ranger) {
    switch(ranger->state) {
        case R_IDLE:
            return RANGER_IDLE_ANIMATION_SPEED;
        case R_MOVING:
            return RANGER_MOVING_ANIMATION_SPEED;
        case R_JUMPING:
            return RANGER_JUMPING_ANIMATION_SPEED;
        case R_ROLL:
            return RANGER_ROLL_ANIMATION_SPEED;
        case R_SLIDE:
        case R_HIT:
        case R_DEAD:
        default:
            return 0;
    }
}

void toggleRangerState(RANGER *ranger, RANGER_STATE newState) {
    if(ranger->state != newState) {
        ranger->state = newState;
        ranger->animationFrame = 0;
        ranger->animationTime.start = SDL_GetTicks();
    }
}

Uint8 getSpriteAnimationRow(RANGER *ranger) {
    Uint8 row = 0;

    if(ranger->state == R_IDLE) return row;
    if(ranger->state == R_MOVING) row = 1;

    return row;
}

char* getStateName(RANGER_STATE state) {
    switch (state) {
        case R_IDLE: return "IDLE";
        case R_MOVING: return "MOVING";
        case R_JUMPING: return "JUMPING";
        case R_HIT: return "HITTED";
        case R_DEAD: return "DEAD";
        default: return "UNKNOWN";
    }
}