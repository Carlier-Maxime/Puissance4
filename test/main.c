/**
 * @file test/main.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the main of test program
 * @version 0.1
 * @date 2022-12-17
 * @copyright Copyright (c) 2022
 */

#include <CUnit/Basic.h>
#include "grid.h"
#include "viewTerminal.h"
#include "player.h"
#include "playerHuman.h"
#include "playerAIEasy.h"

/**
 * execute different unit test
 * @return CU_get_error()
 */
int main() {
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    CU_Suite *grid = TestGrid_create();
    if (!grid) goto quit;
    CU_Suite *viewTerminal = TestViewTerminal_create();
    if (!viewTerminal) goto quit;
    CU_Suite *player = TestPlayer_create();
    if (!player) goto quit;
    CU_Suite *playerHuman = TestPlayerHuman_create();
    if (!playerHuman) goto quit;
    CU_Suite *playerAIEasy = TestPlayerAIEasy_create();
    if (!playerAIEasy) goto quit;
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
quit:
    CU_cleanup_registry();
    return CU_get_error();
}