//
// Created by Lenovo on 08/12/2022.
//

#ifndef PUISSANCE4_VIEW_H
#define PUISSANCE4_VIEW_H

#include "grid.h"

typedef struct View_{
    Grid *grid;
    void *data;
    void (*render)(struct View_ *view);
    void (*destroy)(struct View_ *view);
} View;

#endif //PUISSANCE4_VIEW_H
