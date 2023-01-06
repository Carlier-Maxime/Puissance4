/**
 * @file test/playerAIHard.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the player AI hard implementation
 * @version 0.1
 * @date 2023-01-06
 * @copyright Copyright (c) 2023
 */

#include <stdlib.h>
#include "playerAIHard.h"

static short choiceColumn(View *view, const unsigned char val) {
    return PlayerAIBase_choiceColumn(view,val,4);
}

Player *PlayerAIHard_create(const char* name) {
    Player *p = PlayerAIBase_create(name);
    if (!p) return NULL;
    p->choiceColumn = choiceColumn;
    return p;
}