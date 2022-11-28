/**
 * \file
 * \brief Matrix implementation
 */
#include "matrix.h"

#include "vector.h"

#include <assert.h>
#include <stdlib.h>

struct MAT_Matrix * MAT_alloc(
    const int rows,
    const int cols)
{
    struct MAT_Matrix *const matrix = calloc(1, sizeof(*matrix));

    const int number_of_elements = rows * cols;

    matrix->data = calloc((size_t)number_of_elements, sizeof(*matrix->data));
    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

void MAT_free(
    struct MAT_Matrix *const matrix)
{
    free(matrix->data);
    free(matrix);
}

void MAT_set_element(
    struct MAT_Matrix *const matrix,
    const int row,
    const int col,
    const double value)
{
    assert(row < matrix->rows); // LCOV_EXCL_LINE
    assert(col < matrix->cols); // LCOV_EXCL_LINE

    matrix->data[(matrix->cols * row) + col] = value;
} // LCOV_EXCL_LINE

void MAT_set_all_elements(
    struct MAT_Matrix *const matrix,
    const double value)
{
    for (int r = 0; r < matrix->rows; ++r)
    {
        for (int c = 0; c < matrix->cols; ++c)
        {
            MAT_set_element(matrix, r, c, value);
        }
    }
}

double MAT_get_element(
    const struct MAT_Matrix *const matrix,
    const int row,
    const int col)
{
    assert(row < matrix->rows); // LCOV_EXCL_LINE
    assert(col < matrix->cols); // LCOV_EXCL_LINE

    return matrix->data[(matrix->cols * row) + col];
}

void MAT_transpose_square(
    struct MAT_Matrix *const matrix)
{
    for (int r = 1; r < matrix->rows; ++r)
    {
        for (int c = 0; c < r; ++c)
        {
            const double temp = MAT_get_element(matrix, r, c);
            MAT_set_element(matrix, r, c, MAT_get_element(matrix, c, r));
            MAT_set_element(matrix, c, r, temp);
        }
    }

    const int temp = matrix->rows;
    matrix->rows = matrix->cols;
    matrix->cols = temp;
}

void MAT_matrix_matrix_multiplication(
    const struct MAT_Matrix *const a,
    const struct MAT_Matrix *const b,
    struct MAT_Matrix *const output)
{
    assert(b->rows == a->cols); // LCOV_EXCL_LINE
    assert(output->rows == a->rows); // LCOV_EXCL_LINE
    assert(output->cols == b->cols); // LCOV_EXCL_LINE

    for (int r = 0; r < output->rows; ++r)
    {
        for (int c = 0; c < output->cols; ++c)
        {
            double sum = 0.0;

            for (int i = 0; i < a->cols; ++i)
            {
                sum += MAT_get_element(a, r, i) * MAT_get_element(b, i, c);
            }

            MAT_set_element(output, r, c, sum);
        }
    }
}

void MAT_matrix_vector_multiplication(
    const struct MAT_Matrix *const matrix,
    const struct VEC_Vector *const vector,
    struct VEC_Vector *const output)
{
    assert(vector->length == matrix->cols); // LCOV_EXCL_LINE
    assert(output->length == matrix->rows); // LCOV_EXCL_LINE

    for (int i = 0; i < output->length; ++i)
    {
        double sum = 0.0;

        for (int j = 0; j < vector->length; ++j)
        {
            sum += MAT_get_element(matrix, i, j) * VEC_get_element(vector, j);
        }

        VEC_set_element(output, i, sum);
    }
}
