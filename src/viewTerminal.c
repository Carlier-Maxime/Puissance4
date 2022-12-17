/**
 * @file src/viewTerminal.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view terminal implementation
 * @version 0.1
 * @date 2022-12-12
 * @copyright Copyright (c) 2022
 */

#include <stdlib.h>
#include <stdio.h>
#include "viewTerminal.h"

/**
 * @enum ErrorCode
 * @brief the enumeration of error code of view
 */
typedef enum {
    NO_ERROR, //!< no recent errors to report
    NO_MEMORY_ERROR, //!< not enough free memory
    NO_SELF_ERROR, //!< no self is provided
    NO_GRID_ERROR //!< the grid is null
} ErrorCode;

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
 * destroy the view
 * @param view self
 */
static void destroy(View *view) {
    if (!view) return;
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
char* ViewTerminal_getErrorMsg() {
    switch (errorCode) {
        case 0: return "no recent errors to report";
        case 1: return "not enough free memory";
        case 2: return "no self is provided";
        case 3: return "the grid is null";
        default: return "an error has occurred, this error has no description.";
    }
}

/**
 * print error in stderr
 */
void ViewTerminal_printError() {
    fprintf(stderr,"ViewTerminal Error : %s (code=%d)\n",ViewTerminal_getErrorMsg(),ViewTerminal_getErrorCode());
}