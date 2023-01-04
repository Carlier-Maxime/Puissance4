/**
 * @file src/view.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view implementation
 * @version 0.1
 * @date 2023-01-04
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
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
}