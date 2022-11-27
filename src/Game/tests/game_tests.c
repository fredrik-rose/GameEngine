#include "../game.h"

#include "Base/common.h"
#include "TestFramework/test_framework.h"

#include <stdio.h>

int TF_test_case_status;

static void test_GAME_run(void)
{
    /*
     * The purpose of this test is to:
     *     - Make sure the gamed does not crash
     *     - Make sure no asserts fails
     *     - Catch memory management problems by running address sanitizers and valgrind
     *     - Catch undefined behavior during runtime
     * This test does thus not really testing the functionality. Consider excluding it from coverage
     * reports.
     */

    /*
     * Disable printf to avoid game outputs. This is a hack that might only work on Linux running
     * in a terminal. Note that this will also disable the output from the test runner.
     */
    fclose(stdout);
    GAME_run(100.0, 2);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_GAME_run,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
