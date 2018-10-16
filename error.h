#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ERROR_NULL = 0,
    ERROR_SUCCESS,
    ERROR_FAILURE,
    ERROR_BAD_ALLOC,
    ERROR_FILE_OPEN,
    ERROR_READ_WRITE_FILE,
    ERROR_COUNT,
} error_t;

const char *error_get_string(error_t error);

int error_get_type(error_t error);

void error_print(const char* reason, const char* file, const char* fun, int line);

#ifdef __cplusplus
}
#endif

#endif /* ERROR_H */

