/**
 * @file src/player.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_PLAYER_H
#define PUISSANCE4_PLAYER_H

typedef struct View_ View; //!< pre declaration of view

#include "view.h"
#include "error.h"

/**
 * @struct Player
 * @brief A structure to represent an player
 */
typedef struct Player_ {
    char* name; //!< the name of player

    /**
     * choose the column to place the token in the desired location
     * @param view used for current game
     * @return index column
     */
    short (*choiceColumn)(View *view, const unsigned char val);

    /**
     * destroy the player
     * @param player (self)
     */
    void (*destroy)(struct Player_ *player);
} Player;

/**
 * @enum PlayerType
 * @brief A enumeration of player type
 */
typedef enum PlayerType_ {
    PLAYER_NONE,
    PLAYER_HUMAN,
    PLAYER_AI_EASY
} PlayerType;

/**
 * get error code
 * @return the value of error code (use Player_getErrorMsg() for more information)
 */
ErrorCode Player_getErrorCode();

/**
 * get error message of the player error code
 * @return message corresponding the player error code based on ErrorCode enumeration (error.h)
 */
const char* Player_getErrorMsg();

/**
 * set the player error code to given value
 * @param code : new error code value
 */
void Player_setError(ErrorCode code);

/**
 * print player error code in the stderr
 * format : "Player Error : %s (code=%d)\n"
 * %s : message
 * %d : error code value
 */
void Player_printError();

/**
 * create player with type specified
 * @param type of player
 * @return new player with type specified
 */
Player *Player_create(PlayerType type, const char *name);

#endif //PUISSANCE4_PLAYER_H
