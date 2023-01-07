/**
 * @file src/view.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view implementation
 * @version 0.1
 * @date 2023-01-07
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "viewTerminal.h"
#include "viewSDL.h"
#include "error.h"

static ErrorCode errorCode; //!< the error code of view

ErrorCode View_getErrorCode() {
    return errorCode;
}

const char* View_getErrorMsg() {
    return Error_getMsg(errorCode);
}

void View_setError(ErrorCode code) {
    errorCode=code;
}

void View_printError() {
    fprintf(stderr,"View Error : %s\n",View_getErrorMsg());
    if (errorCode==SDL_ERROR) fprintf(stderr,"SDL Error : %s\n",SDL_GetError());
}

View *View_create(ViewType type, Grid *grid) {
    switch (type) {
        case VIEW_NONE: return NULL;
        case VIEW_TERMINAL: return ViewTerminal_create(grid);
        case VIEW_SDL: return ViewSDL_create(grid);
        default:
            errorCode=UNKNOWN_TYPE;
            return NULL;
    }
}