/**
 * @file test/playerAIEasy.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player ai easy implementation
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#include <stdlib.h>
#include "PlayerAIEasy.h"
#include "PlayerAIBase.h"
#include "error.h"

static short choiceColumn(View *view, const unsigned char tokenValue) {
    if (!view) {
        Player_setError(NO_VIEW_ERROR);
        return -1;
    }
    Grid *g = view->grid;
    for (short i = 0; i < GRID_WIDTH; i++) {
        g->placeToken(g,i,tokenValue);
        if (g->isInWinAlignment(g,i)) {
            g->removeTopToken(g,i);
            Player_setError(NO_ERROR);
            return i;
        }
        g->removeTopToken(g,i);
    }
    for (short i = 0; i < GRID_WIDTH; i++) {
        g->placeToken(g,i,(tokenValue==1) ? 2 : 1);
        if (g->isInWinAlignment(g,i)) {
            g->removeTopToken(g,i);
            Player_setError(NO_ERROR);
            return i;
        }
        g->removeTopToken(g,i);
    }
    Player_setError(NO_ERROR);
    return (short) (rand()%(6+1));
}

Player *PlayerAIEasy_create(const char* name) {
    Player *p = PlayerAIBase_create(name);
    p->choiceColumn = choiceColumn;
    return p;
}