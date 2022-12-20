#include "error.h"

const char* Error_getMsg(unsigned errorCode) {
    switch (errorCode) {
        case NO_ERROR: return "no recent errors to report";
        case NO_MEMORY_ERROR: return "not enough free memory";
        case NO_SELF_ERROR: return "no self is provided";
        case COLUMN_OUT_OF_RANGE_ERROR: return "the provided column is out of range";
        case TOKEN_VALUE_ERROR: return "the supplied token value is not allowed";
        case NO_SPACE_IN_COLUMN_ERROR: return "no space left in provided column";
        case NO_GRID_ERROR: return "the grid is null";
        default: return "an error has occurred, this error has no description.";
    }
}