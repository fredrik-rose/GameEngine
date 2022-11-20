/**
 * \brief Vector interface
 */
#ifndef VECTOR_H
#define VECTOR_H

/**
 * \brief Vector with dynamic length
 */
struct VEC_Vector
{
    int length; /**< Number of elements in the vector */
    double *data; /**< The elements of the vector */
};

/**
 * \brief Update the value of an element in a vector
 *
 * \param[in,out] vector The vector
 * \param[in] pos The position to update
 * \param[in] value The new value
 */
void VEC_set_element(
    struct VEC_Vector *const vector,
    const int pos,
    const double value);

/**
 * \brief Get a certain element from a vector
 *
 * \param[in] vector The vector
 * \param[in] pos The position to extract the element from
 *
 * \return The element
 */
double VEC_get_element(
    const struct VEC_Vector *const vector,
    const int pos);

/**
 * \brief Calculate the norm of a vector
 *
 * \param[in] vector The vector
 *
 * \return The norm
 */
double VEC_norm(
    const struct VEC_Vector *const vector);

/**
 * \brief Normalize a vector so that it becomes a unit vector (in place)
 *
 * \param[in,out] vector The vector to normalize
 */
void VEC_normalize(
    struct VEC_Vector *const vector);

/**
 * \brief Calculate the dot product of two vectors.
 *
 * \param[in] a The first vector
 * \param[in] b The second vector
 *
 * \return The dot product of the two vectors
 */
double VEC_dot_product(
    const struct VEC_Vector *const a,
    const struct VEC_Vector *const b);

#endif /* VECTOR_H */
