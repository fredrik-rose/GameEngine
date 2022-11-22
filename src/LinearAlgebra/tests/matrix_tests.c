#include "../matrix.h"
#include "../vector.h"

#include "Base/common.h"
#include "TestFramework/test_framework.h"

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_MAT_transpose_square(void)
{
    double values[][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    double expected_values[][3] = {
        {1.0, 4.0, 7.0},
        {2.0, 5.0, 8.0},
        {3.0, 6.0, 9.0}
    };
    struct MAT_Matrix matrix = {
        .rows = LENGTH(values),
        .cols = LENGTH(values[0]),
        .data = &values[0][0]
    };

    MAT_transpose_square(&matrix);

    TF_assert(matrix.rows == LENGTH(expected_values));
    TF_assert(matrix.cols == LENGTH(expected_values[0]));

    for (int r = 0; r < matrix.rows; ++r)
    {
        for (int c = 0; c < matrix.cols; ++c)
        {
            const double actual = MAT_get_element(&matrix, r, c);
            const double expected = expected_values[r][c];

            TF_assert_double_eq(actual, expected, granularity);
        }
    }
}

static void test_MAT_matrix_matrix_multiplication(void)
{
    double a_values[][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };
    double b_values[][2] = {
        {11.0, 12.0},
        {13.0, 14.0},
        {15.0, 16.0}
    };
    double expected_values[][2] = {
        {82.0, 88.0},
        {199.0, 214.0}
    };

    struct MAT_Matrix a = {
        .rows = LENGTH(a_values),
        .cols = LENGTH(a_values[0]),
        .data = &a_values[0][0]
    };
    struct MAT_Matrix b = {
        .rows = LENGTH(b_values),
        .cols = LENGTH(b_values[0]),
        .data = &b_values[0][0]
    };

    struct MAT_Matrix *const output = MAT_alloc(LENGTH(expected_values), LENGTH(expected_values[0]));

    MAT_matrix_matrix_multiplication(&a, &b, output);

    for (int r = 0; r < output->rows; ++r)
    {
        for (int c = 0; c < output->cols; ++c)
        {
            const double actual = MAT_get_element(output, r, c);
            const double expected = expected_values[r][c];

            TF_assert_double_eq(actual, expected, granularity);
        }
    }

    MAT_free(output);
}

static void test_MAT_matrix_vector_multiplication(void)
{
    double matrix_values[][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };
    double vector_values[] = {
        11.0, 12.0, 13.0
    };
    double expected_values[] = {
        74.0, 182.0
    };

    struct MAT_Matrix matrix = {
        .rows = LENGTH(matrix_values),
        .cols = LENGTH(matrix_values[0]),
        .data = &matrix_values[0][0]
    };
    struct VEC_Vector vector = {
        .length = LENGTH(vector_values),
        .data = &vector_values[0]
    };

    struct VEC_Vector *const output = VEC_alloc(LENGTH(expected_values));

    MAT_matrix_vector_multiplication(&matrix, &vector, output);

    for (int i = 0; i < output->length; ++i)
    {
        const double actual = VEC_get_element(output, i);
        const double expected = expected_values[i]; // NOLINT Incorrectly assumes 'i' will have the value 2.

        TF_assert_double_eq(actual, expected, granularity);
    }

    VEC_free(output);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_MAT_transpose_square,
        test_MAT_matrix_matrix_multiplication,
        test_MAT_matrix_vector_multiplication,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
