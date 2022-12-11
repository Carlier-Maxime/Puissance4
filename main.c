#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "viewTerminal.h"

int main() {
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
