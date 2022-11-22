/**
 * \file
 * \brief Common interface
 */
#ifndef BASE_COMMON_H
#define BASE_COMMON_H

/** Use to specify that a function parameter is not used */
#define UNUSED(param) ((void)(param))

/** Get the number of elements of an array (pointers are not supported) */
#define LENGTH(array) (sizeof(array) / sizeof(*(array)))

#endif /* BASE_COMMON_H */
