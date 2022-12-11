#include <stdio.h>
#include "grid.h"
#include "viewTerminal.h"

int main() {
    Grid *g = Grid_create();
    View *v = ViewTerminal_create(g);
    v->render(v);
    g->placeToken(g,2,1);
    v->render(v);
    v->destroy(v);
    g->destroy(g);
    return 0;
}
