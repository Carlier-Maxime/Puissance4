/**
 * @file src/grid.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the game grid
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_GRID_H
#define PUISSANCE4_GRID_H

#include <stdbool.h>
#include "error.h"

/**
 * @def GRID_HEIGHT
 * @brief the height of the grid
 */
#define GRID_HEIGHT 6

/**
 * @def GRID_WIDTH
 * @brief the width of the grid
 */
#define GRID_WIDTH 7

/**
 * @struct Grid
 * @brief A structure to represent the game grid
 */
typedef struct grid_{
    /**
     * the tab is grid representation
     * the value signification :
     *  0 : no token
     *  1 : token of player 1
     *  2 : token of player 2
     */
    unsigned char tab[GRID_HEIGHT][GRID_WIDTH];

    /**
     * destroy grid
     * @param grid (self)
     */
    void (*destroy)(struct grid_ *grid);

    /**
     * place token in grid
     * @param grid self
     * @param column where the token should be inserted
     * @param val the value of the token (1|2)
     * @return true if success
     * @return false if failure (use Grid_getErrorCode() or Grid_getErrorMsg() for more information)
     * Error possible :
     * - NO_SELF_ERROR
     * - COLUMN_OUT_OF_RANGE_ERROR
     * - TOKEN_VALUE_ERROR
     * - NO_SPACE_IN_COLUMN_ERROR
     * - NO_ERROR
     */
    bool (*placeToken)(struct grid_ *grid, const unsigned char column, const unsigned char val);

    /**
     * check if last add of the column is in an alignment of 4 or more tokens
     * @param grid (self)
     * @param column : grid column index
     * @return true if last add in column is in an win alignment else false
     */
    bool (*isInWinAlignment)(struct grid_ *grid, const unsigned char column);

    /**
     * reset grid for empty the tab
     * @param grid self
     * @return true if success
     * @return false if failure (use Grid_getErrorCode() or Grid_getErrorMsg() for more information)
     * Error possible :
     * - NO_SELF_ERROR
     * - NO_ERROR
     */
    bool (*reset)(struct grid_ *grid);

    /**
     * Removes the top token from the specified column in the given grid.
     *
     * @param grid The grid containing the token to be removed.
     * @param column The column from which to remove the top token.
     * @return true if a token was successfully removed, false if failure (use Grid_getErrorCode() or Grid_getErrorMsg() for more information).
     * Error possible :
     * - NO_SELF_ERROR
     * - COLUMN_OUT_OF_RANGE_ERROR
     * - NO_TOKEN_IN_COLUMN
     * - NO_ERROR
     */
    bool (*removeTopToken)(struct grid_ *grid, const unsigned char column);
} Grid;

/**
 * create new grid
 * @return new grid
 * @return NULL if failure (use Grid_getErrorCode() or Grid_getErrorMsg() for more information)
 * Error possible :
 * - NO_MEMORY_ERROR
 * - NO_ERROR
 */
Grid* Grid_create();

/**
 * get grid error code
 * @return value of error code (use Grid_getErrorMsg() for more information)
 */
ErrorCode Grid_getErrorCode();

/**
 * get grid error message (cover all error in ErrorCode)
 * @return error message based on error code
 */
const char* Grid_getErrorMsg();

/**
 * print error in stderr
 * format : "Grid Error : %s (code=%d)\n"
 * %s : message
 * %d : error code value
 */
void Grid_printError();

#endif //PUISSANCE4_GRID_H
