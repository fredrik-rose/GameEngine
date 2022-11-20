/**
 * \brief Common interface
 */

/** Get the number of elements of an array (pointers are not supported) */
#define LENGTH(array) (sizeof(array) / sizeof(*(array)))
