
#ifndef PUISSANCE4_ERROR_H
#define PUISSANCE4_ERROR_H

typedef enum {
    NO_ERROR, //!< no recent errors to report
    NO_MEMORY_ERROR, //!< not enough free memory
    NO_SELF_ERROR, //!< no self is provided
    COLUMN_OUT_OF_RANGE_ERROR, //!< the provided column is out of range
    TOKEN_VALUE_ERROR, //!< the supplied token value is not allowed
    NO_SPACE_IN_COLUMN_ERROR, //!< no space left in provided column
    NO_GRID_ERROR //!< the grid is null
} ErrorCode;

const char* Error_getMsg(unsigned errorCode);

#endif //PUISSANCE4_ERROR_H
