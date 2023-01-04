/**
 * @file test/playerAIEasy.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player ai easy
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_PLAYERAIEASY_H
#define PUISSANCE4_PLAYERAIEASY_H

#include "player.h"

/**
 * create the easy ai player
 * @param name of the player (not null)
 * @return new easy ai player
 */
Player *PlayerAIEasy_create(const char* name);

#endif //PUISSANCE4_PLAYERAIEASY_H
