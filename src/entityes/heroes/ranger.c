#include "ranger.h"

RANGER initRanger(void) {
    RANGER ranger;

    ranger.pos.x = 100;
    ranger.pos.y = 100;

    initRangerSprites(&ranger);

    return ranger;
}

void initRangerSprites(RANGER *ranger) {
    ranger->sprites.idle[0] = 0;

}