/**
 * @file test/playerAIBase.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player ai base implementation
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "playerAIBase.h"
#include "error.h"

static bool initRng=false; //!< boolean is false before initRandom()

/**
 * initialize random value
 */
static void initRandom() {
    srand(time(NULL)*GRID_WIDTH);
    initRng=true;
}

static void destroy(Player *player) {
    if (!player) {
        Player_setError(NO_SELF_ERROR);
        return;
    }
    free(player->name);
    free(player);
    Player_setError(NO_ERROR);
}

Player *PlayerAIBase_create(const char* name) {
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
            NULL,
            destroy
    };
    if (!player->name) {
        Player_setError(NO_MEMORY_ERROR);
        return NULL;
    }
    Player_setError(NO_ERROR);
    if (!initRng) initRandom();
    return player;
}