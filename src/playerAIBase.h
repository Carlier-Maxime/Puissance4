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

/**
 * choice best column for optimise probability of win
 * @param view : the view
 * @param tokenValue : the value of your token
 * @param depth : traversal depth to calculate the win weight of each column
 * 0: test only on your current round
 * 1: test on your current round and your next round
 * 3: test on your current round and your next 3 round
 * @return index column
 */
short PlayerAIBase_choiceColumn(View *view, unsigned char tokenValue, unsigned char depth);

#endif //PUISSANCE4_PLAYERAIBASE_H
