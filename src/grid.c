/**
 * @file src/grid.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the game grid implementation
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "error.h"

static ErrorCode errorCode=NO_ERROR; //!< last grid error

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
    unsigned char i=GRID_HEIGHT-1;
    while (grid->tab[i][column] && i>0) i--;
    if (grid->tab[i][column]) {
        errorCode=NO_SPACE_IN_COLUMN_ERROR;
        return false;
    }
    grid->tab[i][column]=val;
    errorCode=NO_ERROR;
    return true;
}

/**
 * check if the index token [row][column] is in an vertical alignment of 4 or more tokens
 * @param grid (self)
 * @param column : grid column index
 * @param row : grid row index
 * @return true if the index token [row][column] is in an win vertical alignment else false
 */
bool isInWinAlignmentVertical(Grid *grid, const unsigned char column, unsigned char row) {
    unsigned char nbToken=0, val=grid->tab[row][column];
    while (row<GRID_HEIGHT && grid->tab[row][column]==val) {
        nbToken++;
        row++;
    }
    return nbToken>=4;
}

/**
 * check if the index token [row][column] is in an horizontal alignment of 4 or more tokens
 * @param grid (self)
 * @param column : grid column index
 * @param row : grid row index
 * @return true if the index token [row][column] is in an win horizontal alignment else false
 */
bool isInWinAlignmentHorizontal(Grid *grid, char column, const unsigned char row) {
    unsigned char nbToken=0, val=grid->tab[row][column];
    while (column>=0 && grid->tab[row][column]==val) {
        nbToken++;
        column--;
    }
    column=(char)(column+nbToken+1);
    while (column<GRID_WIDTH && grid->tab[row][column]==val) {
        nbToken++;
        column++;
    }
    return nbToken>=4;
}

/**
 * check if the index token [row][column] is in an diagonal alignment of 4 or more tokens
 * @param grid (self)
 * @param column : grid column index
 * @param row : grid row index
 * @return true if the index token [row][column] is in an win diagonal alignment else false
 */
bool isInWinAlignmentDiagonal(Grid *grid, char column, char row) {
    unsigned char nbToken=0, val=grid->tab[row][column];
    while (row>=0 && column>=0 && grid->tab[row][column]==val) {
        nbToken++;
        column--;
        row--;
    }
    row=(char)(row+nbToken+1);
    column=(char)(column+nbToken+1);
    char tmp = 0;
    while (row<GRID_HEIGHT && column<GRID_WIDTH && grid->tab[row][column]==val) {
        tmp++;
        column++;
        row++;
    }
    row=(char)(row-(tmp+1));
    column=(char)(column-(tmp+1));
    nbToken+=tmp;
    if (nbToken>=4) return true;
    nbToken=0;
    while (row<GRID_HEIGHT && column>=0 && grid->tab[row][column]==val) {
        nbToken++;
        column--;
        row++;
    }
    row=(char)(row-(nbToken+1));
    column=(char)(column+nbToken+1);
    while (row>=0 && column<GRID_WIDTH && grid->tab[row][column]==val) {
        nbToken++;
        column++;
        row--;
    }
    return nbToken>=4;
}

static bool isInWinAlignment(Grid *grid, const unsigned char column) {
    if (!grid) {
        errorCode=NO_SELF_ERROR;
        return false;
    }
    if (column>=GRID_WIDTH) {
        errorCode=COLUMN_OUT_OF_RANGE_ERROR;
        return false;
    }
    unsigned char row=GRID_HEIGHT-1;
    while (grid->tab[row][column] && row>0) row--;
    if (!grid->tab[row][column]) row++;
    errorCode=NO_ERROR;
    if (row>=GRID_HEIGHT) return false;
    return isInWinAlignmentVertical(grid,column,row) || isInWinAlignmentHorizontal(grid,(char) column,row) || isInWinAlignmentDiagonal(grid, (char) column,(char) row);
}

static void destroy(Grid* grid) {
    if (!grid) return;
    free(grid);
    errorCode=NO_ERROR;
}

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

bool removeTopToken(struct grid_ *grid, const unsigned char column) {
    if (!grid) {
        errorCode=NO_SELF_ERROR;
        return false;
    }
    if (column>=GRID_WIDTH) {
        errorCode=COLUMN_OUT_OF_RANGE_ERROR;
        return false;
    }
    unsigned char i=0;
    while (!grid->tab[i][column] && i<GRID_HEIGHT) i++;
    if (i>=GRID_HEIGHT) {
        errorCode=NO_TOKEN_IN_COLUMN;
        return false;
    }
    grid->tab[i][column]=0;
    errorCode=NO_ERROR;
    return true;
}

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
            isInWinAlignment,
            reset,
            removeTopToken
    };
    errorCode=NO_ERROR;
    return grid;
}

ErrorCode Grid_getErrorCode() {
    return errorCode;
}

const char* Grid_getErrorMsg() {
    return Error_getMsg(errorCode);
}

void Grid_printError() {
    fprintf(stderr,"Grid Error : %s (code=%d)\n",Grid_getErrorMsg(),Grid_getErrorCode());
}