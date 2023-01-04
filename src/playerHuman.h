/**
 * @file src/playerHuman.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player human
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_PLAYERHUMAN_H
#define PUISSANCE4_PLAYERHUMAN_H

#include "player.h"

/**
 * create the human player
 * @param name of the player (not null)
 * @return new human player
 */
Player *PlayerHuman_create(const char* name);

#endif //PUISSANCE4_PLAYERHUMAN_H
