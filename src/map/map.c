#include "map.h"
#include "graphics/window.h"

MAP initMap() {
    char mapName[256] = "assets/maps/map.txt";
    FILE* fp;
    MAP map = { 0 };

    if ((fp = fopen(mapName, "rb")) == NULL) {
        logMessage(LOG_ERROR, "Failed to open map file: %s", mapName);
        return map;
    }
    logMessage(LOG_INFO, "Map file opened successfully with name: %s", mapName);

    map.width = 15;
    map.height = 18;

    map.tiles = (int**)malloc(map.height * sizeof(int*));
    for (int y = 0; y < map.height; y++) {
        map.tiles[y] = (int*)malloc(map.width * sizeof(int));
        for(int x = 0; x < map.width; x++) {
            if(fscanf(fp, "%d", &map.tiles[y][x]) != 1) {
                logMessage(LOG_ERROR, "Failed to read map file at position: [%d, %d]", y, x);
            }
        }
    }

    fclose(fp);
    return map;
}

void freeMap(MAP* map) {
    for (int y = 0; y < map->height; y++) {
        free(map->tiles[y]);
    }
    free(map->tiles);
}

void renderMap(MAP* map) {
    /*SDL_Renderer* renderer = getRenderer();

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            int type = map->tiles[y][x];

            switch (type) {
                case TT_VOID:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); break;
                case TT_GROUND:
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); break;
                case TT_PLATFORM:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); break;
            }

            SDL_Rect rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            SDL_RenderFillRect(renderer, &rect);
        }
    }*/

    SDL_Renderer* renderer = getRenderer();
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    for(int i = 0; i < GAME_WIDTH / TILE_SIZE; i++) {
        for(int j = 0; j < GAME_HEIGHT / TILE_SIZE; j++) {
            SDL_Rect tileRect = { i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            SDL_RenderDrawRect(renderer, &tileRect);
        }
    }
}

