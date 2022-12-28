/**
 * @file test/viewTerminal.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the viewTerminal testing implementation
 * @version 0.1
 * @date 2022-12-28
 * @copyright Copyright (c) 2022
 */

#include "viewTerminal.h"
#include "../src/viewTerminal.h"
#include "../src/error.h"

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
    CU_ASSERT(ViewTerminal_getErrorCode()==NO_ERROR)
}

/**
 * test choiceColumn
 */
static void Test_ChoiceColumn() {
    vt->choiceColumn(NULL);
    CU_ASSERT(ViewTerminal_getErrorCode()==NO_ERROR)
    vt->choiceColumn(vt);
    CU_ASSERT(ViewTerminal_getErrorCode()==NO_ERROR)
}

/**
 * test destroy the viewTerminal
 */
static void Test_Destroy() {
    vt->destroy(vt);
    CU_ASSERT(ViewTerminal_getErrorCode()==NO_ERROR)
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
        (NULL == CU_add_test(viewTerminal, "destroy", Test_Destroy)))
    {
        fprintf(stderr,"Error : add test for view terminal suite failed !\n");
        return NULL;
    }
    return viewTerminal;
}