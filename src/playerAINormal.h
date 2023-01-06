/**
 * @file test/playerAINormal.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player AI normal
 * @version 0.1
 * @date 2023-01-06
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_PLAYERAINORMAL_H
#define PUISSANCE4_PLAYERAINORMAL_H

#include "playerAIBase.h"

/**
 * create the normal ai player
 * @param name of the player (not null)
 * @return new normal ai player
 */
Player *PlayerAINormal_create(const char* name);

#endif //PUISSANCE4_PLAYERAINORMAL_H
