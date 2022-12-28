/**
 * @file src/view.c
 * @authors Maxime Carlier and Mohammed Pombo
 * @brief the view implementation
 * @version 0.1
 * @date 2022-12-28
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include "error.h"

static ErrorCode errorCode; //!< the error code of view

/**
 * get error code
 * @return the value of error code (use View_getErrorMsg() for more information)
 */
unsigned View_getErrorCode() {
    return errorCode;
}

/**
 * get error message of the view error code
 * @return message corresponding the view error code based on ErrorCode enumeration (error.h)
 */
const char* View_getErrorMsg() {
    return Error_getMsg(errorCode);
}

/**
 * set the view error code to given value
 * @param code : new error code value
 */
void View_setError(unsigned code) {
    errorCode=code;
}

/**
 * print view error code in the stderr
 */
void View_printError() {
    fprintf(stderr,"View Error : %s\n",View_getErrorMsg());
}