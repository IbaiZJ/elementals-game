#include "text.h"

TTF_Font* font = NULL;

int initText(void) {
    if(font == NULL) {
        font = TTF_OpenFontIndex("assets/fonts/Inter.ttf", 16, 0);
        if(font == NULL) {
            logMessage(LOG_ERROR, "Failed to load font! SDL_ttf Error: %s", TTF_GetError());
            return -1;
        }
    }

    return 1;
}

void destroyText(void) {
    if(font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }
}

void renderText(int x, int y, char *text, SDL_Color color) {
    if(font == NULL) {
        logMessage(LOG_ERROR, "Font not initialized! Call initText() first.");
        return;
    }

    SDL_Surface* textSurface;
	SDL_Texture* mTexture;
    SDL_Rect src, dst;
	SDL_Renderer* gRenderer;

    gRenderer = getRenderer();
    textSurface = TTF_RenderText_Solid(font, text, color);
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    src.x = 0; dst.x = x;
	src.y = 0; dst.y = y;
	src.w = dst.w = textSurface->w;
	src.h = dst.h = textSurface->h;
	SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(mTexture);
}

