#include <CUnit/Basic.h>
#include "../src/grid.h"

static Grid *g = NULL;

void testCreate() {
    g=Grid_create();
    CU_ASSERT(g!=NULL);
}

void testDestroy() {
    g->destroy(g);
    CU_ASSERT(Grid_getErrorCode()==0);
}

int main() {
    CU_pSuite grid=NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    grid = CU_add_suite("Grid", NULL, NULL);
    if (!grid) {
        fprintf(stderr,"Error : add suite failed !\n");
        goto quit;
    }
    if ((NULL == CU_add_test(grid, "create", testCreate)) ||
        (NULL == CU_add_test(grid, "destroy", testDestroy)))
    {
        fprintf(stderr,"Error : add suite failed !\n");
        goto quit;
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
quit:
    CU_cleanup_registry();
    return CU_get_error();
}