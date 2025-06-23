#include "ranger.h"

RANGER initRanger(void) {
    RANGER ranger;

    ranger.pos.x = 100;
    ranger.pos.y = 100;
    ranger.state = R_IDLE;
    ranger.animationTime.start = SDL_GetTicks();
    ranger.animationFrame = 0;

    initRangerSprites(&ranger);

    return ranger;
}

void initRangerSprites(RANGER *ranger) {
    ranger->sprites.base = loadTexture("assets/img/ranger/ranger_288x128_SpriteSheet.png");
    scaleImage(ranger->sprites.base, 288 * RANGER_SCALE, 128 * RANGER_SCALE);
    logMessage(LOG_INFO, "Ranger sprites initialized");
}

void renderRanger(RANGER *ranger) {
    renderTextureFrames(ranger->sprites.base, (int[]){ ranger->animationFrame, ranger->state}, 288, 128);
}

void moveRanger(RANGER *ranger) {
    INPUTS* input = getInput();
    float dt = getDeltaTime();

    if(input->left) {
        ranger->pos.x -= RANGER_SPEED * dt;
    }
    if(input->right) {
        ranger->pos.x += RANGER_SPEED * dt;
    }

    if(input->jump && ranger->isOnGround) {
        ranger->velocityY = RANGER_JUMP_FORCE;
        ranger->isOnGround = false;
    }

    ranger->velocityY += RANGER_GRAVITY * dt;
    ranger->pos.y += ranger->velocityY * dt;

    if (ranger->pos.y >= 500.0f) {
        ranger->pos.y = 500.0f;
        ranger->velocityY = 0;
        ranger->isOnGround = true;
    }

    moveImage(ranger->sprites.base, ranger->pos.x, ranger->pos.y);
}

void animateRanger(RANGER *ranger) {
    ranger->animationTime.finish = SDL_GetTicks();
    if(ranger->animationTime.finish - ranger->animationTime.start > RANGER_ANIMATION_SPEED) {
        ranger->animationTime.start += RANGER_ANIMATION_SPEED;
        if(ranger->animationFrame < RANGER_IDLE_ANIMATION_FRAMES - 1 ) {
            ranger->animationFrame++;
        }
        else ranger->animationFrame = 0;
    }
}