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

ErrorCode Player_getErrorCode() {
    return errorCode;
}

const char* Player_getErrorMsg() {
    return Error_getMsg(errorCode);
}

void Player_setError(unsigned code) {
    errorCode = code;
}

void Player_printError() {
    fprintf(stderr,"Player Error : %s (code=%d)\n",Player_getErrorMsg(),errorCode);
}

