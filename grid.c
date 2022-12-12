/**
 * @file grid.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the game grid implementation
 * @version 0.1
 * @date 2022-12-12
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

/**
 * @enum ErrorCode
 * @brief the enumeration of error code of grid
 */
typedef enum {
    NO_ERROR, //!< no recent errors to report
    NO_MEMORY_ERROR, //!< not enough free memory
    NO_SELF_ERROR, //!< no self is provided
    COLUMN_OUT_OF_RANGE_ERROR, //!< the provided column is out of range
    TOKEN_VALUE_ERROR, //!< the supplied token value is not allowed
    NO_SPACE_IN_COLUMN_ERROR //!< no space left in provided column
} ErrorCode;

static ErrorCode errorCode=NO_ERROR; //!< last grid error

/**
 * place token in grid
 * @param grid self
 * @param column where the token should be inserted
 * @param val the value of the token (1|2)
 * @return true if success
 * @return false if failure (use Grid_getErrorCode() or Grid_getErrorMsg() for more information)
 */
static bool placeToken(Grid *grid, const unsigned char column, const unsigned char val) {
    if (!grid) {
        errorCode=NO_SELF_ERROR;
        return false;
    }
    if (column>=GRID_WIDTH) {
        errorCode=COLUMN_OUT_OF_RANGE_ERROR;
        return false;
    }
    if (val != 1 && val != 2) {
        errorCode=TOKEN_VALUE_ERROR;
        return false;
    }
    unsigned i=GRID_HEIGHT-1;
    while (grid->tab[i][column] && i>0) i--;
    if (grid->tab[i][column]) {
        errorCode=NO_SPACE_IN_COLUMN_ERROR;
        return false;
    }
    grid->tab[i][column]=val;
    errorCode=NO_ERROR;
    return true;
}

static void destroy(Grid* grid) {
    if (!grid) return;
    free(grid);
    errorCode=NO_ERROR;
}

/**
 * reset grid for empty the tab
 * @param grid self
 * @return true if success
 * @return false if failure (use Grid_getErrorCode() or Grid_getErrorMsg() for more information)
 */
static bool reset(Grid *grid) {
    if (!grid) {
        errorCode=NO_SELF_ERROR;
        return false;
    }
    for (unsigned i=0; i<GRID_HEIGHT; i++) {
        for (unsigned j = 0; j < GRID_WIDTH; j++) {
            grid->tab[i][j]=0;
        }
    }
    errorCode=NO_ERROR;
    return true;
}

/**
 * create new grid
 * @return new grid
 * @return NULL if failure (use Grid_getErrorCode() or Grid_getErrorMsg() for more information)
 */
Grid* Grid_create() {
    Grid *grid = malloc(sizeof(Grid));
    if (!grid) {
        errorCode=NO_MEMORY_ERROR;
        return NULL;
    }
    *grid = (Grid) {
            {},
            destroy,
            placeToken,
            reset
    };
    errorCode=NO_ERROR;
    return grid;
}

/**
 * get grid error code
 * @return value of error code (use Grid_getErrorMsg() for more information)
 */
unsigned Grid_getErrorCode() {
    return errorCode;
}

/**
 * get grid error message
 * @return error message based on error code
 */
char* Grid_getErrorMsg() {
    switch (errorCode) {
        case 0: return "no recent errors to report";
        case 1: return "not enough free memory";
        case 2: return "no self is provided";
        case 3: return "the provided column is out of range";
        case 4: return "the supplied token value is not allowed";
        case 5: return "no space left in provided column";
        default: return "an error has occurred, this error has no description.";
    }
}

/**
 * print error in stderr
 */
void Grid_printError() {
    fprintf(stderr,"Grid Error : %s (code=%d)\n",Grid_getErrorMsg(),Grid_getErrorCode());
}