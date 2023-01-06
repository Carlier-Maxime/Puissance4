/**
 * @file src/viewSDL.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view SDL
 * @version 0.1
 * @date 2023-01-07
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_VIEWSDL_H
#define PUISSANCE4_VIEWSDL_H

#include "view.h"

/**
 * create new view SDL
 * @param grid the grid pointer
 * @return new view SDL
 * @return NULL if failure (use View_getErrorCode() or View_getErrorMsg() for more information)
 */
View* ViewSDL_create(Grid *grid);

#endif //PUISSANCE4_VIEWSDL_H
