//
// Created by Lenovo on 11/12/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "viewTerminal.h"

typedef enum {
    NO_ERROR,
    NO_MEMORY_ERROR,
    NO_SELF_ERROR,
    NO_GRID_ERROR
} ErrorCode;

static ErrorCode errorCode;

static void render(View *view) {
    if (!view) {
        errorCode=NO_SELF_ERROR;
        return;
    }
    if (!view->grid) {
        errorCode=NO_GRID_ERROR;
        return;
    }
    printf("--PUISSANCE 4--\n");
    for (unsigned i=0; i<GRID_HEIGHT; i++) {
        bool is_floor = i==GRID_HEIGHT-1;
        printf("|");
        for (unsigned j=0; j<GRID_WIDTH; j++) {
            switch (view->grid->tab[i][j]) {
                case 1:
                    printf("X|");
                    break;
                case 2:
                    printf("O|");
                    break;
                default: printf("%c|",is_floor ? '_' : ' ');
            }
        }
        printf("\n");
    }
    printf("\n");
    errorCode=NO_ERROR;
}

static void destroy(View *view) {
    if (!view) {
        errorCode=NO_SELF_ERROR;
        return;
    }
    free(view);
    errorCode=NO_ERROR;
}

View* ViewTerminal_create(Grid *grid) {
    if (!grid) {
        errorCode=NO_GRID_ERROR;
        return NULL;
    }
    View *v = (View *) malloc(sizeof(View));
    if (!v) {
        errorCode=NO_MEMORY_ERROR;
        return NULL;
    }
    *v = (View) {
            grid,
            NULL,
            render,
            destroy
    };
    errorCode=NO_ERROR;
    return v;
}

unsigned ViewTerminal_getErrorCode() {
    return errorCode;
}

char* ViewTerminal_getErrorMsg() {
    switch (errorCode) {
        case 0: return "no recent errors to report";
        case 1: return "not enough free memory";
        case 2: return "no self is provided";
        case 3: return "the grid is null";
        default: return "an error has occurred, this error has no description.";
    }
}