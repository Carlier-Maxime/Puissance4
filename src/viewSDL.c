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
        for (unsigned char j=0; j<GRID_HEIGHT; j++) {
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

static short choiceColumn(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return -1;
    }
    // ViewSDL *data = view->data;
    SDL_Event  *event = malloc(sizeof(SDL_Event));
    while (1) {
        SDL_PollEvent(event);
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            int x,y;
            SDL_GetMouseState(&x,&y);
            for (unsigned char i=0; i<GRID_WIDTH; i++) {
                if (x>(VIEW_WIDTH/GRID_WIDTH)*i && x<(VIEW_WIDTH/GRID_WIDTH)*(i+1)) return i;
            }
        }
    }
}

static bool showPlayer(View *view, Player *player) {
    //TODO
    return true;
}

static bool win(View *view, Player *player) {
    //TODO
    return true;
}

static bool invalidColumn(View *view, unsigned char column) {
    //TODO
    return true;
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
    SDL_Color colors[4] = {{0,255,0,255}, {255,255,0,255}, {255,165,0,255}, {255,0,0,255}};
    PlayerType playerTypes[4] = {PLAYER_HUMAN,PLAYER_AI_EASY,PLAYER_AI_NORMAL,PLAYER_AI_HARD};
    SDL_Rect rects[4] = {{VIEW_WIDTH/16,VIEW_HEIGHT/2,VIEW_HEIGHT/6,VIEW_HEIGHT/6}};
    rects[0].y -= rects[0].h/2;
    for (unsigned char i=1; i < 4; i++) {
        rects[i] = rects[i - 1];
        rects[i].x += rects[i].w + rects[0].x;
    }
    for (unsigned char i = 0; i < 4; i++) {
        if (SDL_SetRenderDrawColor(data->renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a) != 0 ||
            SDL_RenderFillRect(data->renderer, &rects[i]) != 0) {
            View_setError(SDL_ERROR);
            return PLAYER_NONE;
        }
    }
    SDL_RenderPresent(data->renderer);
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
    //TODO
    return false;
}

static void destroy(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return;
    }
    ViewSDL *data = view->data;
    SDL_DestroyTexture(data->textureChoiceColumn);
    SDL_DestroyTexture(data->textureGrid);
    SDL_DestroyRenderer(data->renderer);
    SDL_DestroyWindow(data->window);
    SDL_Quit();
    free(data);
    free(view);
}

View* ViewSDL_create(Grid *grid) {
    if (!grid) {
        View_setError(NO_GRID_ERROR);
        return NULL;
    }
    View *v = (View *) malloc(sizeof(View));
    if (!v) {
        View_setError(NO_MEMORY_ERROR);
        return NULL;
    }
    if (SDL_Init(SDL_INIT_VIDEO)!=0) {
        View_setError(SDL_ERROR);
        return NULL;
    }
    ViewSDL *data = malloc(sizeof(ViewSDL));
    if (!data) {
        View_setError(NO_MEMORY_ERROR);
        free(v);
        return NULL;
    }
    SDL_Window *window = SDL_CreateWindow("Puissance 4",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,VIEW_WIDTH,VIEW_HEIGHT,0);
    if (!window) {
        View_setError(SDL_ERROR);
        free(data);
        free(v);
        return NULL;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        free(data);
        free(v);
        View_setError(SDL_ERROR);
        return NULL;
    }
    SDL_Texture *textureGrid = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, VIEW_WIDTH,(VIEW_HEIGHT/(GRID_HEIGHT+1))*6);
    if (!textureGrid) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        free(data);
        free(v);
        View_setError(SDL_ERROR);
        return NULL;
    }
    SDL_Texture *textureChoiceColumn = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, VIEW_WIDTH,VIEW_HEIGHT/(GRID_HEIGHT+1));
    if (!textureChoiceColumn) {
        SDL_DestroyTexture(textureGrid);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        free(data);
        free(v);
        View_setError(SDL_ERROR);
        return NULL;
    }
    *data = (ViewSDL) {
        window,
        renderer,
        textureGrid,
        textureChoiceColumn
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
}