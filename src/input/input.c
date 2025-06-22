#include "input.h"

SDL_Event event;
INPUTS input;

void initInputs() {
    input.quit = false;
    input.speedUP = false;
    input.speedDOWN = false;
    input.shot = false;
    input.specialShot = false;
    input.focus = false;
    input.mousePos.x = 0;
    input.mousePos.y = 0;
    input.renderCollitions = 0;
}

void pollEvents() {
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            input.quit = true;
            break;
        }
        if(event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                input.focus = true;
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                input.focus = false;
            }
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    input.quit = true;
                case SDLK_UP:
                case SDLK_w:
                    input.speedUP = true;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    input.speedDOWN = true;
                    break;
                case SDLK_e:
                    input.specialShot = true;
                    break;
                case SDLK_c:
                    input.renderCollitions = 1 - input.renderCollitions;
                    break;
                default:
                    break;
            }
        }
        if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    input.speedUP = false;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    input.speedDOWN = false;
                    break;
                case SDLK_e:
                    input.specialShot = false;
                    break;
                default:
                    break;
            }
        }
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if(event.button.button == SDL_BUTTON_LEFT) {
                input.shot = true;
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP) {
            if(event.button.button == SDL_BUTTON_LEFT) {
                input.shot = false;
            }
        }
        if(event.type == SDL_MOUSEMOTION) {
            input.mousePos.x = event.motion.x;
            input.mousePos.y = event.motion.y;
        }
    }
}

void exitEvent(Uint8 *quit) {
    if(input.quit) *quit = 1; 
}