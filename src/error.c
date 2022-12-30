/**
 * @file src/error.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the error system
 * @version 0.1
 * @date 2022-12-30
 * @copyright Copyright (c) 2022
 */

#include "error.h"

/**
 * allows to get the given error code message
 * @param errorCode based on enumeration ErrorCode
 * @return message correspondent of the given error code
 */
const char* Error_getMsg(unsigned errorCode) {
    switch (errorCode) {
        case NO_ERROR: return "no recent errors to report";
        case NO_MEMORY_ERROR: return "not enough free memory";
        case NO_SELF_ERROR: return "no self is provided";
        case COLUMN_OUT_OF_RANGE_ERROR: return "the provided column is out of range";
        case TOKEN_VALUE_ERROR: return "the supplied token value is not allowed";
        case NO_SPACE_IN_COLUMN_ERROR: return "no space left in provided column";
        case NO_GRID_ERROR: return "the grid is null";
        case NO_NAME_ERROR: return "the name is null";
        case NO_VIEW_ERROR: return "the view is null";
        case NO_PLAYER_ERROR: return "the player is null";
        default: return "an error has occurred, this error has no description.";
    }
}