#include <stdio.h>
#include "grid.h"
#include "viewTerminal.h"

int main() {
    Grid *g = createGrid();
    View *v = ViewTerminal_create(g);
    v->render();
    g->placeToken(g,2,1);
    v->render();
    v->destroy(v);
    destroyGrid(g);
    return 0;
}
