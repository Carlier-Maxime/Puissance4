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

typedef struct viewSDL_ {
    SDL_Window *w;
} viewSDL;

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
    //TODO
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
    *v = (View) {
            grid,
            NULL,
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