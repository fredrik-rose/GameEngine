/**
 * \brief Common interface
 */

/** Use to specify that a function parameter is not used */
#define UNUSED_PARAM(param) ((void)(param))

/** Get the number of elements of an array (pointers are not supported) */
#define LENGTH(array) (sizeof(array) / sizeof(*(array)))
