/**
 * @file test/playerAIEasy.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player ai easy test implementation
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#include "playerAIEasy.h"
#include "../src/playerAIEasy.h"

static Player *p = NULL;

/**
 * test create player
 */
static void Test_create() {
    p = PlayerAIEasy_create(NULL);
    CU_ASSERT(p==NULL)
    CU_ASSERT(Player_getErrorCode()==NO_NAME_ERROR)
    p = PlayerAIEasy_create("Maxime");
    CU_ASSERT(p!=NULL)
    CU_ASSERT(Player_getErrorCode()==NO_ERROR)
}

/**
 * test destroy player
 */
static void Test_destroy() {
    if (!p) {
        p = PlayerAIEasy_create("Mohammed");
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

}

/**
 * clean test player
 * @return
 */
static int Test_Clean() {
    if (p) p->destroy(p);
    return CUE_SUCCESS;
}

CU_Suite *TestPlayerAIEasy_create() {
    CU_Suite *playerAIEasy = CU_add_suite("playerAIEasy",NULL,Test_Clean);
    if (!playerAIEasy) {
        fprintf(stderr,"Error : add playerAIEasy suite failed !\n");
        return NULL;
    }
    if ((NULL == CU_add_test(playerAIEasy,"create",Test_create)) ||
        (NULL == CU_add_test(playerAIEasy,"choiceColumn",Test_choiceColumn)) ||
        (NULL == CU_add_test(playerAIEasy,"destroy",Test_destroy)))
    {
        fprintf(stderr,"Error : add test for playerAIEasy suite failed !\n");
        return NULL;
    }
    return playerAIEasy;
}