/**
 * @file test/viewTerminal.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the viewTerminal testing implementation
 * @version 0.1
 * @date 2022-12-30
 * @copyright Copyright (c) 2022
 */

#include "viewTerminal.h"
#include "../src/viewTerminal.h"
#include "../src/error.h"
#include "../src/playerHuman.h"

static View *vt = NULL; //!< ViewTerminal for testing
static Grid *g = NULL; //!< Grid for testing viewTerminal

/**
 * test create the viewTerminal
 */
static void Test_Create() {
    g = Grid_create();
    CU_ASSERT(g!=NULL)
    vt = ViewTerminal_create(g);
    CU_ASSERT(vt!=NULL)
}

/**
 * test render the viewTerminal
 */
static void Test_Render() {
    vt->render(vt);
    CU_ASSERT(View_getErrorCode()==NO_ERROR)
}

/**
 * test choiceColumn
 */
static void Test_ChoiceColumn() {
    vt->choiceColumn(NULL);
    CU_ASSERT(View_getErrorCode()==NO_ERROR)
    vt->choiceColumn(vt);
    CU_ASSERT(View_getErrorCode()==NO_ERROR)
}

/**
 * test showPlayer
 */
static void Test_ShowPlayer() {
    Player *p = PlayerHuman_create("tester");
    CU_ASSERT(vt->showPlayer(vt,p)==true)
    CU_ASSERT(vt->showPlayer(vt,NULL)==false)
    CU_ASSERT(View_getErrorCode()==NO_PLAYER_ERROR)
    CU_ASSERT(vt->showPlayer(NULL,p)==true)
    CU_ASSERT(View_getErrorCode()==NO_ERROR)
    CU_ASSERT(vt->showPlayer(NULL,NULL)==false)
    CU_ASSERT(View_getErrorCode()==NO_PLAYER_ERROR)
    p->destroy(p);
}

/**
 * test destroy the viewTerminal
 */
static void Test_Destroy() {
    vt->destroy(vt);
    CU_ASSERT(View_getErrorCode()==NO_ERROR)
    g->destroy(g);
}

/**
 * create the test suite for the viewTerminal and add all the necessary tests to it
 * @return viewTerminal suite
 */
CU_Suite *TestViewTerminal_create() {
    CU_Suite *viewTerminal = CU_add_suite("ViewTerminal", NULL, NULL);
    if (!viewTerminal) {
        fprintf(stderr,"Error : add view terminal suite failed !\n");
        return NULL;
    }
    if ((NULL == CU_add_test(viewTerminal, "create", Test_Create)) ||
        (NULL == CU_add_test(viewTerminal, "render", Test_Render)) ||
        (NULL == CU_add_test(viewTerminal, "choiceColumn", Test_ChoiceColumn)) ||
        (NULL == CU_add_test(viewTerminal, "showPlayer", Test_ShowPlayer)) ||
        (NULL == CU_add_test(viewTerminal, "destroy", Test_Destroy)))
    {
        fprintf(stderr,"Error : add test for view terminal suite failed !\n");
        return NULL;
    }
    return viewTerminal;
}