//
// Created by Lenovo on 08/12/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

static bool placeToken(Grid *grid, unsigned char column, unsigned char val) {
    if (!grid) return false;
    if (column>=GRID_WIDTH) return false;
    if (val != 1 && val != 2) return false;
    unsigned i=GRID_HEIGHT-1;
    while (grid->tab[i][column] && i>0) i--;
    if (grid->tab[i][column]) return false;
    grid->tab[i][column]=val;
    return true;
}

Grid* createGrid() {
    Grid *grid = malloc(sizeof(Grid));
    if (!grid) return NULL;
    grid->placeToken = placeToken;
    return grid;
}

void destroyGrid(Grid* grid) {
    if (!grid) return;
    free(grid);
}
