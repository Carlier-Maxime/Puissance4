/**
 * @file src/viewSDL.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view SDL
 * @version 0.1
 * @date 2023-01-07
 * @copyright Copyright (c) 2023
 */

#include <SDL2/SDL.h>
#include <stdlib.h>
#include "viewSDL.h"

#define VIEW_HEIGHT 900
#define VIEW_WIDTH 900

typedef struct ViewSDL_ {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textureGrid;
    SDL_Texture *textureChoiceColumn;
    SDL_Texture *textureEmptyGrid;
} ViewSDL;

static bool render(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return false;
    }
    ViewSDL *data = view->data;
    if (SDL_SetRenderTarget(data->renderer,data->textureGrid)!=0) {
        View_setError(SDL_ERROR);
        return false;
    }
    if (SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 255)!=0 ||
        SDL_RenderClear(data->renderer)!=0) {
        View_setError(SDL_ERROR);
        return false;
    }
    Grid *g = view->grid;
    SDL_Rect rect = {0,0,VIEW_WIDTH/GRID_WIDTH,VIEW_HEIGHT/(GRID_HEIGHT+1)};
    for (unsigned char i=0; i<GRID_HEIGHT; i++) {
        rect.x=0;
        for (unsigned char j=0; j<GRID_WIDTH; j++) {
            if (!g->tab[i][j]) {
                rect.x+=rect.w;
                continue;
            }
            if (SDL_SetRenderDrawColor(data->renderer, 255, (g->tab[i][j]==1) ? 0 : 255, 0, 255) != 0 ||
                SDL_RenderFillRect(data->renderer, &rect) != 0) {
                View_setError(SDL_ERROR);
                return false;
            }
            rect.x+=rect.w;
        }
        rect.y+=rect.h;
    }
    SDL_RenderCopy(data->renderer,data->textureEmptyGrid,NULL,NULL);
    if (SDL_SetRenderTarget(data->renderer,NULL)!=0) {
        View_setError(SDL_ERROR);
        return -1;
    }
    SDL_Rect src = {0,0,VIEW_WIDTH,(VIEW_HEIGHT/(GRID_HEIGHT+1))*6};
    SDL_Rect dst = {0,VIEW_HEIGHT/(GRID_HEIGHT+1),VIEW_WIDTH,(VIEW_HEIGHT/(GRID_HEIGHT+1))*6};
    if (SDL_RenderCopy(data->renderer,data->textureGrid,&src,&dst) != 0) {
        View_setError(SDL_ERROR);
        return false;
    }
    View_setError(NO_ERROR);
    SDL_RenderPresent(data->renderer);
    return true;
}

void indicateColumn(ViewSDL *data, unsigned char column, bool isInvalid) {
    SDL_Rect dst = {0,0,VIEW_WIDTH,VIEW_HEIGHT/(GRID_HEIGHT+1)};
    SDL_SetRenderTarget(data->renderer, data->textureChoiceColumn);
    if (SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 255)!=0 ||
        SDL_RenderClear(data->renderer)!=0) {
        View_setError(SDL_ERROR);
        return;
    }
    SDL_Rect rect = {(VIEW_WIDTH/GRID_WIDTH)*column,0,(VIEW_WIDTH/GRID_WIDTH)/2, (VIEW_HEIGHT/(GRID_HEIGHT+1))};
    rect.x+=rect.w/2;
    SDL_SetRenderDrawColor(data->renderer, isInvalid ? 128 : 255, isInvalid ? 128 : 255, isInvalid ? 128 : 255, 255);
    SDL_RenderFillRect(data->renderer,&rect);
    SDL_SetRenderTarget(data->renderer, NULL);
    SDL_RenderCopy(data->renderer,data->textureChoiceColumn,NULL,&dst);
    SDL_RenderPresent(data->renderer);
}

static short choiceColumn(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return -1;
    }
    ViewSDL *data = view->data;
    SDL_Event *event = malloc(sizeof(SDL_Event));
    unsigned char column=0;
    while (1) {
        SDL_PollEvent(event);
        if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN) {
            int x,y;
            SDL_GetMouseState(&x,&y);
            for (unsigned char i=0; i<GRID_WIDTH; i++) {
                if (x>(VIEW_WIDTH/GRID_WIDTH)*i && x<(VIEW_WIDTH/GRID_WIDTH)*(i+1)) {
                    if (i!=column) {
                        indicateColumn(data,i,view->grid->tab[0][i]!=0);
                        column=i;
                    }
                    if (event->type == SDL_MOUSEBUTTONDOWN) return column;
                }
            }
        }
    }
}

static bool showPlayer(View *view, Player *player) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return false;
    }
    if (!player) {
        View_setError(NO_PLAYER_ERROR);
        return false;
    }
    ViewSDL *data = view->data;
    SDL_SetWindowTitle(data->window, player->name);
    return true;
}

static bool win(View *view, Player *player) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return false;
    }
    if (!player) {
        View_setError(NO_PLAYER_ERROR);
        return false;
    }
    ViewSDL *data = view->data;
    SDL_SetWindowTitle(data->window, "Puissance 4 - Bravo le dernier joueur ?? avoir poser un pion ?? gagner !");
    SDL_Delay(1500);
    return true;
}

static bool invalidColumn(View *view, unsigned char column) {
    return true; // not action because display in real time in choice column
}

static PlayerType choicePlayer(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return PLAYER_NONE;
    }
    ViewSDL *data = view->data;
    if (SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 255)!=0 ||
        SDL_RenderClear(data->renderer)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    SDL_Texture *textures[4];
    SDL_Surface *surface = SDL_LoadBMP("human.bmp");
    textures[0] = SDL_CreateTextureFromSurface(data->renderer,surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("ai_easy.bmp");
    textures[1] = SDL_CreateTextureFromSurface(data->renderer,surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("ai_normal.bmp");
    textures[2] = SDL_CreateTextureFromSurface(data->renderer,surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("ai_hard.bmp");
    textures[3] = SDL_CreateTextureFromSurface(data->renderer,surface);
    SDL_FreeSurface(surface);
    if (!textures[0] || !textures[1] || !textures[2] || !textures[3]) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    PlayerType playerTypes[4] = {PLAYER_HUMAN,PLAYER_AI_EASY,PLAYER_AI_NORMAL,PLAYER_AI_HARD};
    SDL_Rect rects[4] = {{VIEW_WIDTH/16,VIEW_HEIGHT/2,VIEW_HEIGHT/6,VIEW_HEIGHT/6}};
    rects[0].y -= rects[0].h/2;
    for (unsigned char i=1; i < 4; i++) {
        rects[i] = rects[i - 1];
        rects[i].x += rects[i].w + rects[0].x;
    }
    for (unsigned char i = 0; i < 4; i++) {
        SDL_RenderCopy(data->renderer,textures[i],NULL,&rects[i]);
    }
    SDL_RenderPresent(data->renderer);
    for (unsigned char i=1; i < 4; i++) SDL_DestroyTexture(textures[i]);
    SDL_Event *event = malloc(sizeof(SDL_Event));
    while (1) {
        SDL_PollEvent(event);
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            int x,y;
            SDL_GetMouseState(&x,&y);
            for (int i = 0; i < 4; i++) {
                if (x > rects[i].x && x < (rects[i].x + rects[i].w) && y > rects[i].y && y < (rects[i].y + rects[i].h)) {
                    free(event);
                    return playerTypes[i];
                }
            }
        }
    }
}

static bool fakeChoiceColumn(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return false;
    }
    unsigned char column = rand()%6;
    indicateColumn(view->data,column,view->grid->tab[0][column]!=0);
    return true;
}

static void destroy(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return;
    }
    ViewSDL *data = view->data;
    SDL_DestroyTexture(data->textureEmptyGrid);
    SDL_DestroyTexture(data->textureChoiceColumn);
    SDL_DestroyTexture(data->textureGrid);
    SDL_DestroyRenderer(data->renderer);
    SDL_DestroyWindow(data->window);
    SDL_Quit();
    free(data);
    free(view);
}

View* ViewSDL_create(Grid *grid) {
    View *v = NULL;
    ViewSDL *data = NULL;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *textureGrid = NULL, *textureChoiceColumn=NULL, *textureEmptyGrid=NULL;
    if (!grid) {
        View_setError(NO_GRID_ERROR);
        goto failed;
    }
    v = (View *) malloc(sizeof(View));
    if (!v) {
        View_setError(NO_MEMORY_ERROR);
        goto failed;
    }
    if (SDL_Init(SDL_INIT_VIDEO)!=0) {
        View_setError(SDL_ERROR);
        goto failed;
    }
    data = malloc(sizeof(ViewSDL));
    if (!data) {
        View_setError(NO_MEMORY_ERROR);
        goto failed;
    }
    window = SDL_CreateWindow("Puissance 4",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,VIEW_WIDTH,VIEW_HEIGHT,0);
    if (!window) {
        View_setError(SDL_ERROR);
        goto failed;
    }
    renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        View_setError(SDL_ERROR);
        goto failed;
    }
    textureGrid = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, VIEW_WIDTH,(VIEW_HEIGHT/(GRID_HEIGHT+1))*6);
    if (!textureGrid) {
        View_setError(SDL_ERROR);
        goto failed;
    }
    textureChoiceColumn = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, VIEW_WIDTH,VIEW_HEIGHT/(GRID_HEIGHT+1));
    if (!textureChoiceColumn) {
        View_setError(SDL_ERROR);
        goto failed;
    }
    SDL_Surface* surface = SDL_LoadBMP("grid.bmp");
    if (!surface) {
        View_setError(SDL_ERROR);
        goto failed;
    }
    textureEmptyGrid = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    if (!textureEmptyGrid) {
        View_setError(SDL_ERROR);
        goto failed;
    }
    *data = (ViewSDL) {
        window,
        renderer,
        textureGrid,
        textureChoiceColumn,
        textureEmptyGrid
    };
    *v = (View) {
            grid,
            data,
            render,
            choiceColumn,
            showPlayer,
            win,
            invalidColumn,
            choicePlayer,
            fakeChoiceColumn,
            destroy
    };
    View_setError(NO_ERROR);
    return v;
failed:
    if (textureEmptyGrid) SDL_DestroyTexture(textureEmptyGrid);
    if (textureChoiceColumn) SDL_DestroyTexture(textureChoiceColumn);
    if (textureGrid) SDL_DestroyTexture(textureGrid);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (data) free(data);
    if (v) free(v);
    return NULL;
}