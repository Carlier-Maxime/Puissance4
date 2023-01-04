/**
 * @file src/viewTerminal.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view terminal
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_VIEWTERMINAL_H
#define PUISSANCE4_VIEWTERMINAL_H

#include "view.h"

/**
 * create new view terminal
 * @param grid the grid pointer
 * @return new view terminal
 * @return NULL if failure (use ViewTerminal_getErrorCode() or ViewTerminal_getErrorMsg() for more information)
 */
View* ViewTerminal_create(Grid *grid);

#endif //PUISSANCE4_VIEWTERMINAL_H
