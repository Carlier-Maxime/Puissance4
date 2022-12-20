/**
 * @file test/grid.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the game grid testing implementation
 * @version 0.1
 * @date 2022-12-17
 * @copyright Copyright (c) 2022
 */

#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../src/grid.h"
#include "grid.h"

static Grid *g = NULL; // grid for testing

/**
 * create the grid and check that it went well
 */
void testGrid_Create() {
    g=Grid_create();
    CU_ASSERT(g!=NULL)
}

/**
 * test the placement of tokens on each column and
 * verify that out of range values return an error
 */
void testGrid_PlaceToken() {
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

/**
 * test the grid reset
 */
void testGrid_Reset() {
    CU_ASSERT(g!=NULL)
    g->reset(g);
    CU_ASSERT(Grid_getErrorCode()==0)
}

/**
 * test the grid destroy
 */
void testGrid_Destroy() {
    g->destroy(g);
    CU_ASSERT(Grid_getErrorCode()==0)
}

/**
 * create the test suite for the grid and add all the necessary tests to it
 * @return grid suite
 */
CU_Suite *TestGrid_create() {
    CU_Suite *grid = NULL;
    grid = CU_add_suite("Grid", NULL, NULL);
    if (!grid) {
        fprintf(stderr,"Error : add grid suite failed !\n");
        return NULL;
    }
    if ((NULL == CU_add_test(grid, "create", testGrid_Create)) ||
        (NULL == CU_add_test(grid, "placeToken", testGrid_PlaceToken)) ||
        (NULL == CU_add_test(grid, "reset", testGrid_Reset)) ||
        (NULL == CU_add_test(grid, "destroy", testGrid_Destroy)))
    {
        fprintf(stderr,"Error : add test for grid suite failed !\n");
        return NULL;
    }
    return grid;
}