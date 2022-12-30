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
#include "playerHuman.h"

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
    Player *p2=NULL, *p1=NULL;
    g = Grid_create();
    if (!g) {
        fprintf(stderr,"Error : create grid failed !\n");
        Grid_printError();
        goto quit;
    }
    v = ViewTerminal_create(g);
    if (!v) {
        fprintf(stderr,"Error : create view terminal failed !\n");
        View_printError();
        goto quit;
    }
    if (!v->render(v)) {
        fprintf(stderr,"Error : view render failed !\n");
        View_printError();
        goto quit;
    }
    p1 = PlayerHuman_create("player 1");
    if (!p1) {
        fprintf(stderr,"Error : create player 1 failed !\n");
        Player_printError();
        goto quit;
    }
    p2 = PlayerHuman_create("player 2");
    if (!p2) {
        fprintf(stderr,"Error : create player 2 failed !\n");
        Player_printError();
        goto quit;
    }
    Player *p=p1;
    short column=0;
    while (!g->isInWinAlignment(g,column)) {
        v->showPlayer(v,p);
        column = p->choiceColumn(v);
        if (column<0) {
            fprintf(stderr,"Error : choice column failed !\n");
            Player_printError();
            goto quit;
        }
        if (!g->placeToken(g,column,(p==p1) ? 1 : 2)) {
            fprintf(stderr,"Error : grid place token failed !\n");
            Grid_printError();
            goto quit;
        }
        if (!v->render(v)) {
            fprintf(stderr,"Error : view render failed !\n");
            View_printError();
            goto quit;
        }
        if (p==p1) p=p2;
        else p=p1;
    }
    status=EXIT_SUCCESS;
quit:
    if (p2) p2->destroy(p2);
    if (p1) p1->destroy(p1);
    if (v) v->destroy(v);
    if (g) g->destroy(g);
    return status;
}
