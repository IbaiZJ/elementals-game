#include "ranger.h"

RANGER initRanger(void) {
    RANGER ranger;

    ranger.pos.x = 100;
    ranger.pos.y = 100;

    initRangerSprites(&ranger);

    return ranger;
}

void initRangerSprites(RANGER *ranger) {
    for (int i = 1; i <= 12; i++) {
        char path[128];
        snprintf(path, sizeof(path), RANGER_SPRITES_PATH "idle/idle_%d.png", i);
        ranger->sprites.idle[i - 1] = loadTextureAndCropCenterBelow(path, RANGER_WIDTH, RANGER_HEIGHT);
        scaleImage(ranger->sprites.idle[i - 1], RANGER_WIDTH * RANGER_SCALE, RANGER_HEIGHT * RANGER_SCALE);
    }
}

void renderRanger(RANGER *ranger) {
    renderTexture(ranger->sprites.idle[0]);
}

void moveRanger(RANGER *ranger) {
    INPUTS* input = getInput();

    if(input->up) {
        ranger->pos.y -= RANGER_SPEED * getDeltaTime();
    }
    if(input->down) {
        ranger->pos.y += RANGER_SPEED * getDeltaTime();
    }
    if(input->left) {
        ranger->pos.x -= RANGER_SPEED * getDeltaTime();
    }
    if(input->right) {
        ranger->pos.x += RANGER_SPEED * getDeltaTime();
    }

    moveImage(ranger->sprites.idle[0], ranger->pos.x, ranger->pos.y);
}