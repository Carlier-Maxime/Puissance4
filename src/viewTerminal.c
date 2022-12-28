/**
 * @file src/viewTerminal.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view terminal implementation
 * @version 0.1
 * @date 2022-12-28
 * @copyright Copyright (c) 2022
 */

#include <stdlib.h>
#include <stdio.h>
#include "viewTerminal.h"
#include "error.h"

static ErrorCode errorCode; //!< last view error code

/**
 * render the grid
 * @param view self
 * @return true if success
 * @return false if failure (use ViewTerminal_getErrorCode() or ViewTerminal_getErrorMsg() for more information)
 */
static bool render(View *view) {
    if (!view) {
        errorCode=NO_SELF_ERROR;
        return false;
    }
    if (!view->grid) {
        errorCode=NO_GRID_ERROR;
        return false;
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
    return true;
}

/**
 * choose the column to place the token in the desired location
 * @param view (self)
 * @return index column
 */
static short choiceColumn(View *view) {
    printf("Choisie la colonne où inséré ton pion (0-%d) : ",GRID_WIDTH-1);
    short val=-1;
    while (val<0 || val>=GRID_WIDTH) scanf("%hd",&val);
    errorCode=NO_ERROR;
    return val;
}

/**
 * destroy the view
 * @param view self
 */
static void destroy(View *view) {
    if (!view) {
        errorCode=NO_SELF_ERROR;
        return;
    }
    free(view);
    errorCode=NO_ERROR;
}

/**
 * create new view terminal
 * @param grid the grid pointer
 * @return new view terminal
 * @return NULL if failure (use ViewTerminal_getErrorCode() or ViewTerminal_getErrorMsg() for more information)
 */
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
            choiceColumn,
            destroy
    };
    errorCode=NO_ERROR;
    return v;
}

/**
 * get error code
 * @return the value of error code (use ViewTerminal_getErrorMsg() for more information)
 */
unsigned ViewTerminal_getErrorCode() {
    return errorCode;
}

/**
 * get error message
 * @return the error message based on error code
 */
const char* ViewTerminal_getErrorMsg() {
    return Error_getMsg(errorCode);
}

/**
 * print error in stderr
 */
void ViewTerminal_printError() {
    fprintf(stderr,"ViewTerminal Error : %s (code=%d)\n",ViewTerminal_getErrorMsg(),ViewTerminal_getErrorCode());
}