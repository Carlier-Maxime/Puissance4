/**
 * @file test/playerHuman.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the playerHuman testing implementation
 * @version 0.1
 * @date 2022-12-28
 * @copyright Copyright (c) 2022
 */

#include "playerHuman.h"
#include "../src/playerHuman.h"
#include "../src/error.h"
#include "../src/ViewTerminal.h"

static Player *p=NULL; //!< player for testing

/**
 * test create player
 */
static void Test_create() {
    p = PlayerHuman_create(NULL);
    CU_ASSERT(p==NULL)
    CU_ASSERT(Player_getErrorCode()==NO_NAME_ERROR)
    p = PlayerHuman_create("Maxime");
    CU_ASSERT(p!=NULL)
    CU_ASSERT(Player_getErrorCode()==NO_ERROR)
}

/**
 * test destroy player
 */
static void Test_destroy() {
    if (!p) {
        p = PlayerHuman_create("Mohammed");
        CU_ASSERT(p!=NULL)
        CU_ASSERT(Player_getErrorCode()==NO_ERROR)
    }
    p->destroy(NULL);
    CU_ASSERT(Player_getErrorCode()==NO_SELF_ERROR)
    p->destroy(p);
    CU_ASSERT(Player_getErrorCode()==NO_ERROR)
    p=NULL;
}

/**
 * test choice column
 */
static void Test_choiceColumn() {
    p->choiceColumn(NULL);
    CU_ASSERT(Player_getErrorCode()==NO_VIEW_ERROR)
    Grid *g = Grid_create();
    View *v = ViewTerminal_create(g);
    short c = p->choiceColumn(v);
    CU_ASSERT(Player_getErrorCode()==NO_ERROR)
    CU_ASSERT(c>=0)
    CU_ASSERT(c<GRID_WIDTH)
    v->destroy(v);
    g->destroy(g);
}

/**
 * clean test player
 * @return
 */
static int Test_Clean() {
    if (p) p->destroy(p);
    return CUE_SUCCESS;
}

/**
 * create the test suite for the playerHuman and add all the necessary tests to it
 * @return playerHuman suite
 */
CU_Suite *TestPlayerHuman_create() {
    CU_Suite *playerHuman = CU_add_suite("playerHuman",NULL,Test_Clean);
    if (!playerHuman) {
        fprintf(stderr,"Error : add playerHuman suite failed !\n");
        return NULL;
    }
    if ((NULL == CU_add_test(playerHuman,"create",Test_create)) ||
        (NULL == CU_add_test(playerHuman,"choiceColumn",Test_choiceColumn)) ||
        (NULL == CU_add_test(playerHuman,"destroy",Test_destroy)))
    {
        fprintf(stderr,"Error : add test for playerHuman suite failed !\n");
        return NULL;
    }
    return playerHuman;
}