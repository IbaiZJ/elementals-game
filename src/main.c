#include "core/game.h"
#include "log/logger.h"

int main(int argc, char* argv[]) {
    // clearTerminal();

    if(initAll() < 0) {
        return -1;
    }
    gameLoop();
    destroyAll();

    return 0;
}
