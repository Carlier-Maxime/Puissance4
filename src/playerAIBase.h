/**
 * @file test/playerAIBase.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player ai base
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_PLAYERAIBASE_H
#define PUISSANCE4_PLAYERAIBASE_H

#include "player.h"

/**
 * create the base ai player
 * @param name of the player (not null)
 * @return new base ai player
 */
Player *PlayerAIBase_create(const char *name);

#endif //PUISSANCE4_PLAYERAIBASE_H
