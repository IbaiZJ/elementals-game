#include "texture.h"

SPRITE textures[MAX_TEXTURES];
int textureNum = 0;

int loadTexture(char *name) {
    if (textureNum >= MAX_TEXTURES) {
        logMessage(LOG_ERROR, "Max texture limit (%d) reached!", MAX_TEXTURES);
        return -1;
    }

    textures[textureNum].id = textureNum;
    textures[textureNum].tex = IMG_LoadTexture(getRenderer(), name); 
    if (!textures[textureNum].tex) {
        logMessage(LOG_ERROR, "Unable to load texture: %s | SDL_Error: %s", name, SDL_GetError());
        return -1;
    }

    SDL_SetTextureBlendMode(textures[textureNum].tex, SDL_BLENDMODE_BLEND);
    SDL_QueryTexture(textures[textureNum].tex, NULL, NULL, 
        &textures[textureNum].src.w, &textures[textureNum].src.h);

    textures[textureNum].dst.x = textures[textureNum].src.x = 0;
    textures[textureNum].dst.y = textures[textureNum].src.y = 0;
    textures[textureNum].dst.w = textures[textureNum].src.w;
    textures[textureNum].dst.h = textures[textureNum].src.h;

    logMessage(LOG_INFO, "Texture loaded: %s [id=%d, size=%dx%d]", 
               name, textureNum, textures[textureNum].src.w, textures[textureNum].src.h);

    return textureNum++;
}

int loadTextureAndCropCenterBelow(char *name, int w, int h) {
    int texNum = loadTexture(name);
    if (texNum < 0) {
        return -1;
    }

    int texW = textures[texNum].src.w;
    int texH = textures[texNum].src.h;

    int cropX = (texW - w) / 2;
    int cropY = texH - h;

    if (cropX < 0) cropX = 0;
    if (cropY < 0) cropY = 0;

    textures[texNum].src.x = cropX;
    textures[texNum].src.y = cropY;
    textures[texNum].src.w = textures[texNum].dst.w = w;
    textures[texNum].src.h = textures[texNum].dst.h = h;

    return texNum;
}

void renderTexture(int id) {
    if (id < 0 || id >= textureNum) return;
    SDL_RenderCopy(getRenderer(), textures[id].tex, &textures[id].src, &textures[id].dst);
}

void renderTextureFlipHorizontal(int id) {
    if (id < 0 || id >= textureNum) return;
    
    SDL_RenderCopyEx(getRenderer(), textures[id].tex, &textures[id].src, &textures[id].dst, 
        0.0, NULL, SDL_FLIP_HORIZONTAL);
}

void renderTextureGetFlipHorizontal(int id, HORIZONTAL_POSITION horizontalPosition) {
    if (id < 0 || id >= textureNum) return;

    SDL_RenderCopyEx(getRenderer(), textures[id].tex, &textures[id].src, &textures[id].dst, 
        0.0, NULL, getFlipHorizontal(horizontalPosition));
}

void renderTextureFrames(int id, int *frame, int frameW, int frameH) {
    if (id < 0 || id >= textureNum || frame[0] < 0 || frame[1] < 0) return;

    textures[id].src.x = frame[0] * frameW;
    textures[id].src.w = frameW;
    textures[id].src.y = frame[1] * frameH;
    textures[id].src.h = frameH;

    SDL_RenderCopy(getRenderer(), textures[id].tex, &textures[id].src, &textures[id].dst);
}

void renderTextureFramesFlipHorizontal(int id, int *frame, int frameW, int frameH) {
    if (id < 0 || id >= textureNum || frame[0] < 0 || frame[1] < 0) return;

    textures[id].src.x = frame[0] * frameW;
    textures[id].src.w = frameW;
    textures[id].src.y = frame[1] * frameH;
    textures[id].src.h = frameH;

    SDL_RenderCopyEx(getRenderer(), textures[id].tex, &textures[id].src, &textures[id].dst, 
        0.0, NULL, SDL_FLIP_HORIZONTAL);
}

void renderTextureFramesGetFlipHorizontal(int id, int *frame, int frameW, int frameH
        , HORIZONTAL_POSITION horizontalPosition) {
    if (id < 0 || id >= textureNum || frame[0] < 0 || frame[1] < 0) return;

    textures[id].src.x = frame[0] * frameW;
    textures[id].src.w = frameW;
    textures[id].src.y = frame[1] * frameH;
    textures[id].src.h = frameH;

    SDL_RenderCopyEx(getRenderer(), textures[id].tex, &textures[id].src, &textures[id].dst, 
        0.0, NULL, getFlipHorizontal(horizontalPosition));
}

void moveImage(int id, int x, int y) {
    if (id < 0 || id >= textureNum) return;
    textures[id].dst.x = x;
    textures[id].dst.y = y;
}

void scaleImage(int id, int width, int height) {
    if (id < 0 || id >= textureNum) return;
    textures[id].dst.w = width;
    textures[id].dst.h = height;
}

SDL_RendererFlip getFlipHorizontal(HORIZONTAL_POSITION horizontalPosition) {
    if (horizontalPosition == HORIZONTAL_RIGHT) {
        return SDL_FLIP_NONE;
    } else {
        return SDL_FLIP_HORIZONTAL;
    }
}

/*

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
*/
