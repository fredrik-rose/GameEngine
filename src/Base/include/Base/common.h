/**
 * \file
 * \brief Common interface
 */
#ifndef BASE_COMMON_H
#define BASE_COMMON_H

#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <time.h>

/** Use to specify that a function parameter is not used */
#define UNUSED(param) ((void)(param))

/** Get the number of elements of an array (pointers are not supported) */
#define LENGTH(array) (sizeof(array) / sizeof(*(array)))

/** Measure the CPU time of a function.
 * Inputs:
 *     function: The function to execute
 * Outputs
 *     cpu: The CPU on which the function was run (unsigned int)
 *     node: The CPU node on which the function was run (unsigned int)
 *     execution_time: The CPU execution time (long long)
 */
#define TIME_AND_RUN(function, cpu, node, execution_time, ...) \
    do { \
        struct timespec start; \
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); \
        function(__VA_ARGS__); \
        struct timespec end; \
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); \
        getcpu(&cpu, &node); \
        execution_time = \
            ((end.tv_sec - start.tv_sec) * 1000000000LL) + (end.tv_nsec - start.tv_nsec); \
    } while(0)

#endif /* BASE_COMMON_H */
