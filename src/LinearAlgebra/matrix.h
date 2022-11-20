/**
 * \brief Matrix interface
 */
#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

/**
 * \brief Matrix with dynamic size
 */
struct MAT_Matrix
{
    int rows; /**< Number of rows in the matrix */
    int cols; /**< Number of columns in the matrix */
    double *data; /**< The elements of the matrix */
};

/**
 * \brief Update the value of an element in a matrix
 *
 * \param[in,out] matrix The matrix
 * \param[in] row The row to update
 * \param[in] row The column to update
 * \param[in] value The new value
 */
void MAT_set_element(
    struct MAT_Matrix *const matrix,
    const int row,
    const int col,
    const double value);

/**
 * \brief Get a certain element from a mtrix
 *
 * \param[in] vector The vector
 * \param[in] row The row to extract the element from
 * \param[in] row The column to extract the element from
 *
 * \return The element
 */
double MAT_get_element(
    const struct MAT_Matrix *const matrix,
    const int row,
    const int col);

/**
 * \brief Transpose a matrix (in place)
 *
 * \param[in,out] matrix The matrix to transpose
 */
void MAT_transpose(
    struct MAT_Matrix *const matrix);


/**
 * \brief Multiply two matrices
 *
 * \param[in] a An MxN matrix
 * \param[in] b An NxK matrix
 * \param[in,out] output An MxK matrix
 */
void MAT_matrix_matrix_multiplication(
    const struct MAT_Matrix *const a,
    const struct MAT_Matrix *const b,
    struct MAT_Matrix *const output);

/**
 * \brief Multiply a matrix with a column vector.
 *
 * \param[in] matrix An MxN matrix
 * \param[in] vector A vector of length N
 *
 * \param[in,out] output A vector of length M
 */
void MAT_matrix_vector_multiplication(
    const struct MAT_Matrix *const matrix,
    const struct VEC_Vector *const vector,
    struct VEC_Vector *const output);

#endif /* MATRIX_H */
