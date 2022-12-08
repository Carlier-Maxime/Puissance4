//
// Created by Lenovo on 08/12/2022.
//

#ifndef PUISSANCE4_GRID_H
#define PUISSANCE4_GRID_H
#include <stdbool.h>
#define GRID_HEIGHT 6
#define GRID_WIDTH 7

typedef struct grid_{
    unsigned char tab[GRID_HEIGHT][GRID_WIDTH];
    bool (*placeToken)(struct grid_ *g, unsigned char column, unsigned char val);
} grid;

grid* createGrid();
void destroyGrid(grid* g);

#endif //PUISSANCE4_GRID_H
