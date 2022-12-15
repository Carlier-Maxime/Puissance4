#include <CUnit/Basic.h>
#include "../src/grid.h"

static Grid *g = NULL;

void testCreate() {
    g=Grid_create();
    CU_ASSERT(g!=NULL)
}

void testPlaceToken() {
    CU_ASSERT(g!=NULL)
    g->placeToken(g,0,1);
    CU_ASSERT(Grid_getErrorCode()==0)
    g->placeToken(g,1,2);
    CU_ASSERT(Grid_getErrorCode()==0)
    g->placeToken(g,2,1);
    CU_ASSERT(Grid_getErrorCode()==0)
    g->placeToken(g,3,2);
    CU_ASSERT(Grid_getErrorCode()==0)
    g->placeToken(g,4,1);
    CU_ASSERT(Grid_getErrorCode()==0)
    g->placeToken(g,5,2);
    CU_ASSERT(Grid_getErrorCode()==0)
    g->placeToken(g,6,1);
    CU_ASSERT(Grid_getErrorCode()==0)
    g->placeToken(g,6,0);
    CU_ASSERT(Grid_getErrorCode()!=0)
    g->placeToken(g,7,1);
    CU_ASSERT(Grid_getErrorCode()!=0)
}

void testReset() {
    CU_ASSERT(g!=NULL)
    g->reset(g);
    CU_ASSERT(Grid_getErrorCode()==0)
}

void testDestroy() {
    g->destroy(g);
    CU_ASSERT(Grid_getErrorCode()==0)
}

int main() {
    CU_pSuite grid=NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    grid = CU_add_suite("Grid", NULL, NULL);
    if (!grid) {
        fprintf(stderr,"Error : add grid suite failed !\n");
        goto quit;
    }
    if ((NULL == CU_add_test(grid, "create", testCreate)) ||
        (NULL == CU_add_test(grid, "placeToken", testPlaceToken)) ||
        (NULL == CU_add_test(grid, "reset", testReset)) ||
        (NULL == CU_add_test(grid, "destroy", testDestroy)))
    {
        fprintf(stderr,"Error : add test for grid suite failed !\n");
        goto quit;
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
quit:
    CU_cleanup_registry();
    return CU_get_error();
}