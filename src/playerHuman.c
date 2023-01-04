/**
 * @file src/playerHuman.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player human
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2022
 */

#include <stdlib.h>
#include <string.h>
#include "playerHuman.h"
#include "error.h"

/**
 * choose the column to place the token in the desired location
 * @param view used for current game
 * @return index column
 */
static short choiceColumn(View *view, const unsigned char val) {
    if (!view) {
        Player_setError(NO_VIEW_ERROR);
        return -1;
    }
    short column = view->choiceColumn(view);
    if (column<0 || column>=GRID_WIDTH) Player_setError(COLUMN_OUT_OF_RANGE_ERROR);
    else Player_setError(NO_ERROR);
    return column;
}

/**
 * destroy the player
 * @param player (self)
 */
static void destroy(Player *player) {
    if (!player) {
        Player_setError(NO_SELF_ERROR);
        return;
    }
    free(player->name);
    free(player);
    Player_setError(NO_ERROR);
}

/**
 * create the human player
 * @param name of the player (not null)
 * @return new human player
 */
Player *PlayerHuman_create(const char* name) {
    if (!name) {
        Player_setError(NO_NAME_ERROR);
        return NULL;
    }
    Player *player = malloc(sizeof(Player));
    if (!player) {
        Player_setError(NO_MEMORY_ERROR);
        return NULL;
    }
    *player = (Player) {
            strdup(name),
            choiceColumn,
            destroy
    };
    if (!player->name) {
        Player_setError(NO_MEMORY_ERROR);
        return NULL;
    }
    Player_setError(NO_ERROR);
    return player;
}