#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

typedef struct s_sprite {
    int id;
    SDL_Texture* tex;
    SDL_Rect src, dst;
} SPRITE;

int loadTexture(char* str);
void renderTexture(int id);
void renderTextureFlipVertical(int id);
void renderTextureFrames(int id, int frame, int frameWidth);
void renderTextureFrames_Angle(int id, int frame, int frameWidth, double angle);
void renderTextureFlipVerticalFrames(int id, int frame, int frameWidth);
void renderTextureFrames_X_Y(int id, int frameX, int frameY, int frameWidth, int frameHeight);
void renderTextureFrames_X_Y_Angle(int id, int frameX, int frameY, int frameWidth, int frameHeight, float angle);
void moveImage(int id, int x, int y);
void scaleImage(int id, int width, int height);
void scaleImageInScale(int id, int multiply);
void blendImage(int id, int blend);

#endif