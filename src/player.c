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
#include "playerHuman.h"
#include "playerAIEasy.h"
#include "playerAINormal.h"
#include "playerAIHard.h"
#include "error.h"

static ErrorCode errorCode; //!< the player error code

ErrorCode Player_getErrorCode() {
    return errorCode;
}

const char* Player_getErrorMsg() {
    return Error_getMsg(errorCode);
}

void Player_setError(ErrorCode code) {
    errorCode = code;
}

void Player_printError() {
    fprintf(stderr,"Player Error : %s (code=%d)\n",Player_getErrorMsg(),errorCode);
}

Player *Player_create(PlayerType type, const char *name) {
    errorCode=NO_ERROR;
    switch (type) {
        case PLAYER_NONE: return NULL;
        case PLAYER_HUMAN: return PlayerHuman_create(name);
        case PLAYER_AI_EASY: return PlayerAIEasy_create(name);
        case PLAYER_AI_NORMAL: return PlayerAINormal_create(name);
        case PLAYER_AI_HARD: return PlayerAIHard_create(name);
        default:
            errorCode=UNKNOWN_TYPE;
            return NULL;
    }
}