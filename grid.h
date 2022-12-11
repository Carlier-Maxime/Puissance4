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
    void (*destroy)(struct grid_ *grid);
    bool (*placeToken)(struct grid_ *grid, unsigned char column, unsigned char val);
    bool (*reset)(struct grid_ *grid);
} Grid;

Grid* Grid_create();
unsigned Grid_getErrorCode();
char* Grid_getErrorMsg();

#endif //PUISSANCE4_GRID_H
