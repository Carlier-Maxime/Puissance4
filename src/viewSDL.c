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
} ViewSDL;

static bool render(View *view) {
    //TODO
    return false;
}

static short choiceColumn(View *view) {
    //TODO
    return -1;
}

static bool showPlayer(View *view, Player *player) {
    //TODO
    return false;
}

static bool win(View *view, Player *player) {
    //TODO
    return false;
}

static bool invalidColumn(View *view, unsigned char column) {
    //TODO
    return false;
}

static PlayerType choicePlayer(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return PLAYER_NONE;
    }
    ViewSDL *data = view->data;
    if (SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 255)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    if (SDL_RenderClear(data->renderer)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    if (SDL_SetRenderDrawColor(data->renderer, 0, 255, 0, 255)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    SDL_Rect rectHuman = {VIEW_WIDTH/16,VIEW_HEIGHT/2,VIEW_HEIGHT/6,VIEW_HEIGHT/6};
    rectHuman.y -= rectHuman.h/2;
    if (SDL_RenderFillRect(data->renderer,&rectHuman)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    if (SDL_SetRenderDrawColor(data->renderer, 255, 255, 0, 255)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    SDL_Rect rectAIEasy = rectHuman;
    rectAIEasy.x += rectAIEasy.w + rectHuman.x;
    if (SDL_RenderFillRect(data->renderer,&rectAIEasy)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    if (SDL_SetRenderDrawColor(data->renderer, 255, 165, 0, 255)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    SDL_Rect rectAINormal = rectAIEasy;
    rectAINormal.x += rectAINormal.w + rectHuman.x;
    if (SDL_RenderFillRect(data->renderer,&rectAINormal)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    if (SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 255)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    SDL_Rect rectAIHard = rectAINormal;
    rectAIHard.x += rectAIHard.w + rectHuman.x;
    if (SDL_RenderFillRect(data->renderer,&rectAIHard)!=0) {
        View_setError(SDL_ERROR);
        return PLAYER_NONE;
    }
    SDL_RenderPresent(data->renderer);
    SDL_Event *event = malloc(sizeof(SDL_Event));
    while (1) {
        SDL_PollEvent(event);
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            int x,y;
            SDL_GetMouseState(&x,&y);
            if (x>rectHuman.x && x<(rectHuman.x+rectHuman.w) && y>rectHuman.y && y<(rectHuman.y+rectHuman.h)) {
                free(event);
                return PLAYER_HUMAN;
            }
            if (x>rectAIEasy.x && x<(rectAIEasy.x+rectAIEasy.w) && y>rectAIEasy.y && y<(rectAIEasy.y+rectAIEasy.h)) {
                free(event);
                return PLAYER_AI_EASY;
            }
            if (x>rectAINormal.x && x<(rectAINormal.x+rectAINormal.w) && y>rectAINormal.y && y<(rectAINormal.y+rectAINormal.h)) {
                free(event);
                return PLAYER_AI_NORMAL;
            }
            if (x>rectAIHard.x && x<(rectAIHard.x+rectAIHard.w) && y>rectAIHard.y && y<(rectAIHard.y+rectAIHard.h)) {
                free(event);
                return PLAYER_AI_HARD;
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
        return NULL;
    }
    SDL_Window *window = SDL_CreateWindow("Puissance 4",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,VIEW_WIDTH,VIEW_HEIGHT,0);
    if (!window) {
        View_setError(SDL_ERROR);
        return NULL;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        View_setError(SDL_ERROR);
        return NULL;
    }
    *data = (ViewSDL) {
        window,
        renderer
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