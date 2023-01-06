/**
 * @file test/playerAIHard.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player AI hard
 * @version 0.1
 * @date 2023-01-06
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_PLAYERAIHARD_H
#define PUISSANCE4_PLAYERAIHARD_H

#include "playerAIBase.h"

/**
 * create the hard AI player
 * @param name of the player (not null)
 * @return new hard AI player
 */
Player *PlayerAIHard_create(const char* name);

#endif //PUISSANCE4_PLAYERAIHARD_H
