//
// Created by Lenovo on 08/12/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

typedef enum {
    NO_ERROR,
    NO_MEMORY_ERROR,
    NO_SELF_ERROR,
    COLUMN_OUT_OF_RANGE_ERROR,
    TOKEN_VALUE_ERROR,
    NO_SPACE_IN_COLUMN_ERROR
} ErrorCode;

static ErrorCode errorCode=NO_ERROR;

static bool placeToken(Grid *grid, unsigned char column, unsigned char val) {
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

unsigned Grid_getErrorCode() {
    return errorCode;
}

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

void Grid_printError() {
    fprintf(stderr,"Grid Error : %s (code=%d)\n",Grid_getErrorMsg(),Grid_getErrorCode());
}