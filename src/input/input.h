#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "log/logger.h"

typedef struct s_mousepos {
    int x;
    int y;
} MOUSEPOS;

typedef struct s_inputs {
    bool quit;
    bool jump;
    bool rollSlide;
    bool left;
    bool right;
    bool focus;
    MOUSEPOS mousePos;
} INPUTS;

INPUTS* getInput();
int initInputs();
void pollEvents();
void exitEvent(Uint8 *quit);
void destroyInputs();

#endif