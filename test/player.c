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

CU_Suite *TestPlayer_create() {
    CU_Suite *player = CU_add_suite("player",NULL,NULL);
    if (!player) {
        fprintf(stderr,"Error : add player suite failed !\n");
        return NULL;
    }
    if ((NULL == CU_add_test(player,"setError",Test_setError))) {
        fprintf(stderr,"Error : add test for player suite failed !\n");
        return NULL;
    }
    return player;
}