#ifndef DELTA_TIME_H
#define DELTA_TIME_H

#include <SDL2/SDL.h>

#include "ttf/text.h"

extern float deltaTime; 

float getDeltaTime();
void initDeltaTime();
void calculateDeltaTime();

#endif