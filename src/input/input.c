#include "input.h"

SDL_Event event;
INPUTS* input = NULL;

INPUTS* getInput() {
    return input;
}

int initInputs() {
    input = (INPUTS*)malloc(sizeof(INPUTS));
    if (input == NULL) {
        logMessage(LOG_ERROR, "Failed to allocate memory for input structure");
        return -1;
    }

    input->quit = false;
    input->jump = false;
    input->rollSlide = false;
    input->left = false;
    input->right = false;

    input->focus = false;
    input->mousePos.x = 0;
    input->mousePos.y = 0;

    return 1;
}

void destroyInputs() {
    free(input);
    input = NULL;
}

void pollEvents() {
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            input->quit = true;
            break;
        }
        if(event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                input->focus = true;
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                input->focus = false;
            }
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    input->quit = true;
                    break;

                case SDLK_UP:
                case SDLK_w:
                    input->jump = true;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    input->rollSlide = true;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    input->left = true;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    input->right = true;
                    break;


                default:
                    break;
            }
        }
        if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    input->jump = false;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    input->rollSlide = false;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    input->left = false;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    input->right = false;
                    break;
            }
        }
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            // if(event.button.button == SDL_BUTTON_LEFT) {
            //     input.shot = true;
            // }
        }
        if(event.type == SDL_MOUSEBUTTONUP) {
            // if(event.button.button == SDL_BUTTON_LEFT) {
            //     input.shot = false;
            // }
        }
        if(event.type == SDL_MOUSEMOTION) {
            input->mousePos.x = event.motion.x;
            input->mousePos.y = event.motion.y;
        }
    }
}

void exitEvent(Uint8 *quit) {
    if(input->quit) *quit = 1; 
}