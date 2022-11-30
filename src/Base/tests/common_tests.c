#include <Base/common.h>
#include <TestFramework/test_framework.h>

int TF_test_case_status;

static void test_LENGTH(void)
{
    const int array[] = {1, 2, 3};

    UNUSED(array);

    TF_assert(LENGTH(array) == 3);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_LENGTH,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
