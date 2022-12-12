/**
 * @file grid.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the game grid
 * @version 0.1
 * @date 2022-12-12
 * @copyright Copyright (c) 2022
 */

#ifndef PUISSANCE4_GRID_H
#define PUISSANCE4_GRID_H

#include <stdbool.h>

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
    unsigned char tab[GRID_HEIGHT][GRID_WIDTH]; //!< the tab is grid
    void (*destroy)(struct grid_ *grid); //!< destroy function for destroy grid
    bool (*placeToken)(struct grid_ *grid, const unsigned char column, const unsigned char val); //!< placeToken function for place token in grid
    bool (*reset)(struct grid_ *grid); //!< reset function for empty the tab
} Grid;

Grid* Grid_create();
unsigned Grid_getErrorCode();
char* Grid_getErrorMsg();
void Grid_printError();

#endif //PUISSANCE4_GRID_H
