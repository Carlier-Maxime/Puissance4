/**
 * @file src/player.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player implementation
 * @version 0.1
 * @date 2022-12-28
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include "player.h"
#include "error.h"

static ErrorCode errorCode; //!< the player error code

/**
 * get error code
 * @return the value of error code (use Player_getErrorMsg() for more information)
 */
int Player_getErrorCode() {
    return errorCode;
}

/**
 * get error message of the player error code
 * @return message corresponding the player error code based on ErrorCode enumeration (error.h)
 */
const char* Player_getErrorMsg() {
    return Error_getMsg(errorCode);
}

/**
 * set the player error code to given value
 * @param code : new error code value
 */
void Player_setError(unsigned code) {
    errorCode = code;
}

/**
 * print player error code in the stderr
 * @param player (self)
 */
void Player_printError(Player *player) {
    fprintf(stderr,"Player Error : %s (code=%d)\n",Player_getErrorMsg(),errorCode);
}

