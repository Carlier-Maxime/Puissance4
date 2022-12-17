/**
 * @file src/viewTerminal.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view terminal
 * @version 0.1
 * @date 2022-12-12
 * @copyright Copyright (c) 2022
 */

#ifndef PUISSANCE4_VIEWTERMINAL_H
#define PUISSANCE4_VIEWTERMINAL_H

#include "view.h"

View* ViewTerminal_create(Grid *grid);
unsigned ViewTerminal_getErrorCode();
char* ViewTerminal_getErrorMsg();
void ViewTerminal_printError();

#endif //PUISSANCE4_VIEWTERMINAL_H
