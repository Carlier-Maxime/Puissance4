/**
 * @file src/error.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the error system
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_ERROR_H
#define PUISSANCE4_ERROR_H

/**
 * @enum ErrorCode
 * @brief A enumeration of error codes
 */
typedef enum {
    NO_ERROR, //!< no recent errors to report
    NO_MEMORY_ERROR, //!< not enough free memory
    NO_SELF_ERROR, //!< no self is provided
    COLUMN_OUT_OF_RANGE_ERROR, //!< the provided column is out of range
    TOKEN_VALUE_ERROR, //!< the supplied token value is not allowed
    NO_SPACE_IN_COLUMN_ERROR, //!< no space left in provided column
    NO_GRID_ERROR, //!< the grid is null
    NO_NAME_ERROR, //!< the name is null
    NO_VIEW_ERROR, //!< the view is null
    NO_PLAYER_ERROR, //!< the player is null
    NO_TOKEN_IN_COLUMN, //!< the column no contain a token
    UNKNOWN_TYPE, //!< the type is unknown
    SDL_ERROR //!< SDL Error use SDL_GetError() for more information (SDL2/SDL.h)
} ErrorCode;

/**
 * allows to get the given error code message
 * @param errorCode based on enumeration ErrorCode
 * @return message correspondent of the given error code, if not in ErrorCode return default message
 */
const char* Error_getMsg(unsigned errorCode);

#endif //PUISSANCE4_ERROR_H
