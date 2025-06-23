#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct s_mousepos {
    int x;
    int y;
} MOUSEPOS;

typedef struct s_inputs {
    bool quit;
    bool up;
    bool down;
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