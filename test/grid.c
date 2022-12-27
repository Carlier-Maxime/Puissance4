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
#include "../src/error.h"

static Grid *g = NULL; // grid for testing

/**
 * create the grid and check that it went well
 */
static void Test_Create() {
    g=Grid_create();
    CU_ASSERT(g!=NULL)
}

/**
 * test the placement of tokens on each column and
 * verify that out of range values return an error
 */
static void Test_PlaceToken() {
    g->placeToken(g,0,1);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
    g->placeToken(g,1,2);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
    g->placeToken(g,2,1);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
    g->placeToken(g,3,2);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
    g->placeToken(g,4,1);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
    g->placeToken(g,5,2);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
    g->placeToken(g,6,1);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
    g->placeToken(g,6,0);
    CU_ASSERT(Grid_getErrorCode()==TOKEN_VALUE_ERROR)
    g->placeToken(g,6,3);
    CU_ASSERT(Grid_getErrorCode()==TOKEN_VALUE_ERROR)
    g->placeToken(g,7,1);
    CU_ASSERT(Grid_getErrorCode()==COLUMN_OUT_OF_RANGE_ERROR)
}

/**
 * test is in win alignment
 */
static void Test_isInWinAlignment() {
    g->reset(g);
    CU_ASSERT(g->isInWinAlignment(g,0)==0)
    g->placeToken(g,0,1);
    g->placeToken(g,0,1);
    g->placeToken(g,0,1);
    CU_ASSERT(g->isInWinAlignment(g,0)==0)
    g->placeToken(g,0,1);
    CU_ASSERT(g->isInWinAlignment(g,0)==1)
    g->placeToken(g,1,2);
    g->placeToken(g,2,2);
    g->placeToken(g,3,2);
    CU_ASSERT(g->isInWinAlignment(g,2)==0)
    g->placeToken(g,4,2);
    CU_ASSERT(g->isInWinAlignment(g,2)==1)
    g->placeToken(g,1,1);
    g->placeToken(g,1,2);
    g->placeToken(g,2,2);
    g->placeToken(g,2,1);
    g->placeToken(g,3,2);
    g->placeToken(g,3,2);
    CU_ASSERT(g->isInWinAlignment(g,3)==0)
    g->placeToken(g,3,1);
    CU_ASSERT(g->isInWinAlignment(g,3)==1)
}

/**
 * test the grid reset
 */
static void Test_Reset() {
    g->reset(g);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
}

/**
 * test the grid destroy
 */
static void Test_Destroy() {
    g->destroy(g);
    CU_ASSERT(Grid_getErrorCode()==NO_ERROR)
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
    if ((NULL == CU_add_test(grid, "create", Test_Create)) ||
        (NULL == CU_add_test(grid, "placeToken", Test_PlaceToken)) ||
        (NULL == CU_add_test(grid, "reset", Test_Reset)) ||
        (NULL == CU_add_test(grid, "isInWinAlignment", Test_isInWinAlignment)) ||
        (NULL == CU_add_test(grid, "destroy", Test_Destroy)))
    {
        fprintf(stderr,"Error : add test for grid suite failed !\n");
        return NULL;
    }
    return grid;
}