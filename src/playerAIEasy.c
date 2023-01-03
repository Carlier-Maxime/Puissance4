/**
 * @file test/playerAIEasy.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player ai easy implementation
 * @version 0.1
 * @date 2023-01-03
 * @copyright Copyright (c) 2022
 */

#include <stdlib.h>
#include <string.h>
#include "PlayerAIEasy.h"
#include "PlayerAIBase.h"
#include "error.h"

/**
 * choose the column to place the token in the desired location
 * @param view used for current game
 * @return index column
 */
static short choiceColumn(View *view) {
    return (short) (rand()%(6+1));
}

/**
 * create the easy ai player
 * @param name of the player (not null)
 * @return new easy ai player
 */
Player *PlayerAIEasy_create(const char* name) {
    return PlayerAIBase_create(name);
}