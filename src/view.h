/**
 * @file src/view.h
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#ifndef PUISSANCE4_VIEW_H
#define PUISSANCE4_VIEW_H

typedef struct Player_ Player; //!< pre declaration of player

#include "grid.h"
#include "player.h"
#include "error.h"

/**
 * @struct View
 * @brief A structure to represent the view
 */
typedef struct View_{
    Grid *grid; //!< grid pointer
    void *data; //!< additional data

    /**
     * render the grid
     * @param view self
     * @return true if success
     * @return false if failure (use ViewTerminal_getErrorCode() or ViewTerminal_getErrorMsg() for more information)
     */
    bool (*render)(struct View_ *view);

    /**
     * choose the column to place the token in the desired location
     * @param view (self)
     * @return index column
     */
    short (*choiceColumn)(struct View_ *view);

    /**
     * show player information
     * @param view (self)
     * @param player
     * @return true if success
     * @return false if failed
     */
    bool (*showPlayer)(struct View_ *view, Player *player);

    /**
     * show win message
     * @param view (self)
     * @param player as win
     * @return true if success
     * @return false if failed
     */
    bool (*win)(struct View_ *view, Player *player);

    /**
     * indicates that the column is invalid
     * @param view (self)
     * @param column index
     * @return true if success
     * @return false if failure
     */
    bool (*invalidColumn)(struct View_ *view, unsigned char column);

    /**
     * destroy the view
     * @param view self
     */
    void (*destroy)(struct View_ *view);
} View;

/**
 * get error code
 * @return the value of error code (use View_getErrorMsg() for more information)
 */
ErrorCode View_getErrorCode();

/**
 * get error message of the view error code
 * @return message corresponding the view error code based on ErrorCode enumeration (error.h)
 * format : "View Error : %s (code=%d)\n"
 * %s : message
 * %d : error code value
 */
const char* View_getErrorMsg();

/**
 * set the view error code to given value
 * @param code : new error code value
 */
void View_setError(ErrorCode code);

/**
 * print view error code in the stderr
 */
void View_printError();

#endif //PUISSANCE4_VIEW_H
