/**
 * @file view.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view
 * @version 0.1
 * @date 2022-12-12
 * @copyright Copyright (c) 2022
 */

#ifndef PUISSANCE4_VIEW_H
#define PUISSANCE4_VIEW_H

#include "grid.h"

/**
 * @struct View
 * @brief A structure to represent the view
 */
typedef struct View_{
    Grid *grid; //!< grid pointer
    void *data; //!< additional data
    bool (*render)(struct View_ *view); //!< render function for render grid
    void (*destroy)(struct View_ *view); //!< destroy function for destroy view
} View;

#endif //PUISSANCE4_VIEW_H
