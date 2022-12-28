/**
 * @file src/player.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player
 * @version 0.1
 * @date 2022-12-28
 * @copyright Copyright (c) 2022
 */

#ifndef PUISSANCE4_PLAYER_H
#define PUISSANCE4_PLAYER_H

#include "view.h"

/**
 * @struct Player
 * @brief A structure to represent an player
 */
typedef struct player_ {
    char* name; //!< the name of player
    short (*choiceColumn)(View *view); //!< choose the column to place the token in the desired location
    void (*destroy)(struct player_ *player); //!< destroy function for destroy player
} Player;

int Player_getErrorCode();
const char* Player_getErrorMsg();
void Player_setError(unsigned code);
void Player_printError();

#endif //PUISSANCE4_PLAYER_H
