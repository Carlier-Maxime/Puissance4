/**
 * @file src/main.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the main of program of Puissance 4
 * @version 0.1
 * @date 2022-12-12
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "viewTerminal.h"

/**
 * main function (entry of program)
 * @param argc number of argument
 * @param argv list of argument
 * @return 0 if success
 * @return 1 if failure
 */
int main(int argc, char* argv[]) {
    int status=EXIT_FAILURE;
    Grid *g = NULL;
    View *v = NULL;
    g = Grid_create();
    if (!g) {
        fprintf(stderr,"Error : create grid failed !\n");
        Grid_printError();
        goto quit;
    }
    v = ViewTerminal_create(g);
    if (!v) {
        fprintf(stderr,"Error : create view terminal failed !\n");
        ViewTerminal_printError();
        goto quit;
    }
    if (!v->render(v)) {
        fprintf(stderr,"Error : view render failed !\n");
        ViewTerminal_printError();
        goto quit;
    }
    if (!g->placeToken(g,2,1)) {
        fprintf(stderr,"Error : grid place token failed !\n");
        Grid_printError();
        goto quit;
    }
    if (!v->render(v)) {
        fprintf(stderr,"Error : view render failed !\n");
        ViewTerminal_printError();
        goto quit;
    }
    status=EXIT_SUCCESS;
quit:
    if (v) v->destroy(v);
    if (g) g->destroy(g);
    return status;
}
