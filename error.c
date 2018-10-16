#include "error.h"

static const char *const error_message[] = {

    // ERROR_NULL
    "Operation was not successful, NULL returned",
    // ERROR_SUCCESS
    "Successful operation"
    // ERROR_FAILURE
    "An error has occurred",
    // ERROR_BAD_ALLOC
    "Bad memory allocation, malloc, calloc, realloc failed",
    //ERROR_FILE_OPEN
    "Error: opening file unsuccessful",
    //ERROR_READ_WRITE_FILE
    "Error: reading or writing to a file failed"
};

static int error_type[] = {
    ERROR_NULL,
    ERROR_SUCCESS,
    ERROR_FAILURE,    
    ERROR_BAD_ALLOC,
    ERROR_FILE_OPEN,
    ERROR_READ_WRITE_FILE
};


const char *error_get_string(error_t error)
{
    const char *msg = 0;

    if (error < ERROR_COUNT) {
        msg = error_message[error];
    }

    if (0 == msg) {
        assert(0);
        msg = "";
    }

    return msg;
}

int error_get_type(error_t error)
{
    int type = ERROR_FAILURE;

    if (error < ERROR_COUNT) {
        type = error_type[error];
    }

    return type;
}

void error_print(const char* reason, const char* file, const char* fun, int line){
    fprintf(stderr, " error: [%s]: %s: @%d: %s\n", file, fun, line, reason);
    exit(ERROR_FAILURE);
}