#include <stdio.h>
#include "grid.h"

int main() {
    grid *g = createGrid();
    g->placeToken(g,2,1);
    destroyGrid(g);
    return 0;
}
