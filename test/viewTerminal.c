/**
 * @file test/viewTerminal.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the viewTerminal testing implementation
 * @version 0.1
 * @date 2022-12-17
 * @copyright Copyright (c) 2022
 */

#include "viewTerminal.h"
#include "../src/viewTerminal.h"
#include "../src/error.h"

static View *vt = NULL; // ViewTerminal for testing
static Grid *g = NULL; // Grid for testing viewTerminal

/**
 * test create the viewTerminal
 */
void testVt_Create() {
    g = Grid_create();
    CU_ASSERT(g!=NULL)
    vt = ViewTerminal_create(g);
    CU_ASSERT(vt!=NULL)
}

/**
 * test render the viewTerminal
 */
void testVt_Render() {
    vt->render(vt);
    CU_ASSERT(ViewTerminal_getErrorCode()==NO_ERROR)
}

/**
 * test destroy the viewTerminal
 */
void testVt_Destroy() {
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
    if ((NULL == CU_add_test(viewTerminal, "create", testVt_Create)) ||
        (NULL == CU_add_test(viewTerminal, "render", testVt_Render)) ||
        (NULL == CU_add_test(viewTerminal, "destroy", testVt_Destroy)))
    {
        fprintf(stderr,"Error : add test for view terminal suite failed !\n");
        return NULL;
    }
    return viewTerminal;
}