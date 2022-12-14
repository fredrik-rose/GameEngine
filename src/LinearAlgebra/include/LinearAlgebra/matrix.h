/**
 * \file
 * \brief Matrix interface
 */
#ifndef LINEARALGEBRA_MATRIX_H
#define LINEARALGEBRA_MATRIX_H

struct VEC_Vector;

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
 * \brief Allocate a matrix
 *
 * \param[in] rows The number of rows to allocate
 * \param[in] cols The number of columns to allocate
 *
 * \return Allocated matrix, remember to free it with MAT_free() when no longer needed
 */
struct MAT_Matrix * MAT_alloc(
    int rows,
    int cols);

/**
 * \brief Free a matrix
 *
 * \param[in,out] matrix The matrix to free (do not use it anymore)
 */
void MAT_free(
    struct MAT_Matrix *matrix);

/**
 * \brief Update the value of an element in a matrix
 *
 * \param[in,out] matrix The matrix
 * \param[in] row The row to update
 * \param[in] row The column to update
 * \param[in] value The new value
 */
void MAT_set_element(
    struct MAT_Matrix *matrix,
    int row,
    int col,
    double value);

/**
 * \brief Set all elements in matrix a matrix to a certain value
 *
 * \param[in,out] matrix The matrix
 * \param[in] value The value
 */
void MAT_set_all_elements(
    struct MAT_Matrix *matrix,
    double value);

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
    const struct MAT_Matrix *matrix,
    int row,
    int col);

/**
 * \brief Transpose a square matrix (in place)
 *
 * \param[in,out] matrix The square matrix to transpose
 */
void MAT_transpose_square(
    struct MAT_Matrix *matrix);

/**
 * \brief Multiply two matrices
 *
 * \param[in] a An MxN matrix
 * \param[in] b An NxK matrix
 * \param[in,out] output An MxK matrix
 */
void MAT_matrix_matrix_multiplication(
    const struct MAT_Matrix *a,
    const struct MAT_Matrix *b,
    struct MAT_Matrix *output);

/**
 * \brief Multiply a matrix with a column vector.
 *
 * \param[in] matrix An MxN matrix
 * \param[in] vector A vector of length N
 *
 * \param[in,out] output A vector of length M
 */
void MAT_matrix_vector_multiplication(
    const struct MAT_Matrix *matrix,
    const struct VEC_Vector *vector,
    struct VEC_Vector *output);

#endif /* LINEARALGEBRA_MATRIX_H */
