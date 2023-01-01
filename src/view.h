/**
 * @file src/view.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view
 * @version 0.1
 * @date 2023-01-01
 * @copyright Copyright (c) 2022
 */

#ifndef PUISSANCE4_VIEW_H
#define PUISSANCE4_VIEW_H

typedef struct Player_ Player; //!< pre declaration of player

#include "grid.h"
#include "player.h"

/**
 * @struct View
 * @brief A structure to represent the view
 */
typedef struct View_{
    Grid *grid; //!< grid pointer
    void *data; //!< additional data
    bool (*render)(struct View_ *view); //!< render function for render grid
    short (*choiceColumn)(struct View_ *view); //!< choose the column to place the token in the desired location
    bool (*showPlayer)(struct View_ *view, Player *player); //!< show player information
    bool (*win)(struct View_ *view, Player *player); //!< show win message
    bool (*invalidColumn)(struct View_ *view, unsigned char column); //!< indicates that the column is invalid
    void (*destroy)(struct View_ *view); //!< destroy function for destroy view
} View;

unsigned View_getErrorCode();
const char* View_getErrorMsg();
void View_setError(unsigned code);
void View_printError();

#endif //PUISSANCE4_VIEW_H
