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
    bool speedUP;
    bool speedDOWN;
    bool specialShot;
    bool shot;
    bool collisions;
    bool focus;
    MOUSEPOS mousePos;
    Uint8 renderCollitions;
} INPUTS;

void initInputs();
void pollEvents();
void exitEvent(Uint8 *quit);

#endif