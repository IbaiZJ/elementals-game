#include "texture.h"

extern SDL_Renderer* renderer;
SPRITE textures[100];
int textureNum = 0;

int loadTexture(char* str) {
    textures[textureNum].id = textureNum;

    textures[textureNum].tex = IMG_LoadTexture(renderer, str); 
    if(!textures[textureNum].tex) {
        fprintf(stderr, "unable to load %s texture!\n", str);
    }

    SDL_SetTextureBlendMode(textures[textureNum].tex, SDL_BLENDMODE_BLEND);
    SDL_QueryTexture(textures[textureNum].tex, NULL, NULL, 
        &textures[textureNum].src.w, &textures[textureNum].src.h);
    
    textures[textureNum].dst.x = textures[textureNum].src.x = 0;
    textures[textureNum].dst.y = textures[textureNum].src.y = 0;
    textures[textureNum].dst.w = textures[textureNum].src.w;
    textures[textureNum].dst.h = textures[textureNum].src.h;

    textureNum++;
    return (textureNum - 1);
}

void renderTexture(int id) {
    if (id < 0 || id >= textureNum) return;
    SDL_RenderCopy(renderer, textures[id].tex, &textures[id].src, &textures[id].dst);
}

void renderTextureFlipVertical(int id) {
    if (id < 0 || id >= textureNum) return;
    
    SDL_RenderCopyEx(renderer, textures[id].tex, &textures[id].src, &textures[id].dst, 
        0.0, NULL, SDL_FLIP_HORIZONTAL);
}

void renderTextureFrames(int id, int frame, int frameWidth) {
    if (id < 0 || id >= textureNum) return;
    
    textures[id].src.x = frame * frameWidth;
    textures[id].src.w = frameWidth;
    // textures[id].dst.w = frameWidth;
    SDL_RenderCopy(renderer, textures[id].tex, &textures[id].src, &textures[id].dst);
}

void renderTextureFrames_Angle(int id, int frame, int frameWidth, double angle) {
    if (id < 0 || id >= textureNum) return;
    double angle2 = angle * (180.0 / 3.14159265358979323846264338327950288) + 90;
    textures[id].src.x = frame * frameWidth;
    textures[id].src.w = frameWidth;
    // textures[id].dst.w = frameWidth;
    SDL_RenderCopyEx(renderer, textures[id].tex, &textures[id].src, &textures[id].dst, 
        angle2, NULL, SDL_FLIP_NONE);
}

void renderTextureFlipVerticalFrames(int id, int frame, int frameWidth) {
    if (id < 0 || id >= textureNum) return;
    
    textures[id].src.x = frame * frameWidth;
    textures[id].src.w = frameWidth;
    // textures[id].dst.w = frameWidth;
    SDL_RenderCopyEx(renderer, textures[id].tex, &textures[id].src, &textures[id].dst, 
        0.0, NULL, SDL_FLIP_HORIZONTAL);
}

void renderTextureFrames_X_Y(int id, int frameX, int frameY, int frameWidth, int frameHeight) {
    if (id < 0 || id >= textureNum) return;
    
    textures[id].src.x = frameX * frameWidth;
    textures[id].src.y = frameY * frameWidth;
    textures[id].src.w = frameWidth;
    textures[id].src.h = frameHeight;
    textures[id].dst.w = frameWidth;
    textures[id].dst.h = frameHeight;
    SDL_RenderCopyEx(renderer, textures[id].tex, &textures[id].src, &textures[id].dst, 
        0.0, NULL, SDL_FLIP_NONE);
}

void renderTextureFrames_X_Y_Angle(int id, int frameX, int frameY, int frameWidth, int frameHeight, float angle) {
    if (id < 0 || id >= textureNum) return;
    
    textures[id].src.x = frameX * frameWidth;
    textures[id].src.y = frameY * frameWidth;
    textures[id].src.w = frameWidth;
    textures[id].src.h = frameHeight;
    textures[id].dst.w = frameWidth;
    textures[id].dst.h = frameHeight;
    SDL_RenderCopyEx(renderer, textures[id].tex, &textures[id].src, &textures[id].dst, 
        angle, NULL, SDL_FLIP_NONE);
}

void moveImage(int id, int x, int y) {
    if (id < 0 || id >= textureNum) return;
    textures[id].dst.x = x;
    textures[id].dst.y = y;
}

void scaleImage(int id, int width, int height) {
    if (id < 0 || id >= textureNum) return;
    (textures + id)->dst.w = width;
    (textures + id)->dst.h = height;
}

void scaleImageInScale(int id, int multiply) {
    if (id < 0 || id >= textureNum) return;
    (textures + id)->dst.w *= multiply;
    (textures + id)->dst.h *= multiply;
}

void blendImage(int id, int blend) {
    if (id < 0 || id >= textureNum) return;
    if(blend > 255) blend = 255;
    SDL_SetTextureAlphaMod((textures + id)->tex, blend);
    
} 

