//
// Created by Lenovo on 11/12/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "viewTerminal.h"

static void render(View *view) {
    for (unsigned i=0; i<GRID_HEIGHT; i++) {
        for (unsigned j=0; j<GRID_WIDTH; j++) {
            switch (view->grid->tab[i][j]) {
                case 1:
                    printf("X ");
                    break;
                case 2:
                    printf("O ");
                    break;
                default: printf("_ ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

static void destroy(View *view) {
    free(view);
}

View* ViewTerminal_create(Grid *grid) {
    if (!grid) return NULL;
    View *v = (View *) malloc(sizeof(View));
    if (!v) return NULL;
    *v = (View) {
            grid,
            NULL,
            render,
            destroy
    };
    return v;
}