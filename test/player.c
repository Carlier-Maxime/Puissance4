/**
 * @file test/player.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player testing implementation
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */
#include "player.h"
#include "../src/player.h"
#include "../src/error.h"

/**
 * test set error player
 */
static void Test_setError() {
    Player_setError(NO_ERROR);
    CU_ASSERT(Player_getErrorCode()==NO_ERROR)
    Player_setError(NO_MEMORY_ERROR);
    CU_ASSERT(Player_getErrorCode()==NO_MEMORY_ERROR)
    Player_setError(NO_SELF_ERROR);
    CU_ASSERT(Player_getErrorCode()==NO_SELF_ERROR)
}

static void Test_create() {
    CU_ASSERT(Player_create(PLAYER_NONE,"")==NULL)
    CU_ASSERT(Player_getErrorCode()==NO_ERROR)
    CU_ASSERT(Player_create(256,"")==NULL)
    CU_ASSERT(Player_getErrorCode()==UNKNOWN_TYPE)
    CU_ASSERT(Player_create(PLAYER_AI_EASY,NULL)==NULL)
    CU_ASSERT(Player_getErrorCode()==NO_NAME_ERROR)
    Player *p = Player_create(PLAYER_AI_EASY,"tester");
    CU_ASSERT(p!=NULL)
    CU_ASSERT(Player_getErrorCode()==NO_ERROR)
    p->destroy(p);
}

CU_Suite *TestPlayer_create() {
    CU_Suite *player = CU_add_suite("player",NULL,NULL);
    if (!player) {
        fprintf(stderr,"Error : add player suite failed !\n");
        return NULL;
    }
    if ((NULL == CU_add_test(player,"setError",Test_setError)) ||
        (NULL == CU_add_test(player,"create",Test_create))
    ) {
        fprintf(stderr,"Error : add test for player suite failed !\n");
        return NULL;
    }
    return player;
}