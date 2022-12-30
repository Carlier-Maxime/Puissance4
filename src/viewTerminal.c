/**
 * @file src/viewTerminal.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view terminal implementation
 * @version 0.1
 * @date 2022-12-30
 * @copyright Copyright (c) 2022
 */

#include <stdlib.h>
#include <stdio.h>
#include "viewTerminal.h"
#include "error.h"

/**
 * render the grid
 * @param view self
 * @return true if success
 * @return false if failure (use ViewTerminal_getErrorCode() or ViewTerminal_getErrorMsg() for more information)
 */
static bool render(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return false;
    }
    if (!view->grid) {
        View_setError(NO_GRID_ERROR);
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
    View_setError(NO_ERROR);
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
    View_setError(NO_ERROR);
    return val;
}

/**
 * show player information
 * @param view (self)
 * @param player
 * @return true if success
 * @return false if failed
 */
static bool showPlayer(View *view, Player *player) {
    if (!player) {
        View_setError(NO_PLAYER_ERROR);
        return false;
    }
    printf("%s\n",player->name);
    View_setError(NO_ERROR);
    return true;
}

/**
 * destroy the view
 * @param view self
 */
static void destroy(View *view) {
    if (!view) {
        View_setError(NO_SELF_ERROR);
        return;
    }
    free(view);
    View_setError(NO_ERROR);
}

/**
 * create new view terminal
 * @param grid the grid pointer
 * @return new view terminal
 * @return NULL if failure (use ViewTerminal_getErrorCode() or ViewTerminal_getErrorMsg() for more information)
 */
View* ViewTerminal_create(Grid *grid) {
    if (!grid) {
        View_setError(NO_GRID_ERROR);
        return NULL;
    }
    View *v = (View *) malloc(sizeof(View));
    if (!v) {
        View_setError(NO_MEMORY_ERROR);
        return NULL;
    }
    *v = (View) {
            grid,
            NULL,
            render,
            choiceColumn,
            showPlayer,
            destroy
    };
    View_setError(NO_ERROR);
    return v;
}