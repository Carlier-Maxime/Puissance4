//
// Created by Lenovo on 11/12/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "viewTerminal.h"

static void render() {
    printf("render !\n");
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