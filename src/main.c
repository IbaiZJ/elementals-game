#include "core/game.h"

int main(int argc, char* argv[]) {

    if(initAll() < 0) {
        return -1;
    }
    gameLoop();
    destroyAll();

    return 0;
}