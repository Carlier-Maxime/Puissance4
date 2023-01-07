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

#define VIEW_HEIGHT 700
#define VIEW_WIDTH 700

typedef struct ViewSDL_ {
    SDL_Window *w;
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
    //TODO
    return false;
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
    SDL_DestroyWindow(data->w);
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
    SDL_Window *w = SDL_CreateWindow("Puissance 4",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,VIEW_WIDTH,VIEW_HEIGHT,0);
    if (!w) {
        View_setError(SDL_ERROR);
        return NULL;
    }
    *data = (ViewSDL) {
        w
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