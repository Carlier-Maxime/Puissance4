#include <CUnit/Basic.h>
#include "grid.h"

int main() {
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    CU_Suite *grid = TestGrid_create();
    if (!grid) goto quit;
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
quit:
    CU_cleanup_registry();
    return CU_get_error();
}