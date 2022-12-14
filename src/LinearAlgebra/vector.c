/**
 * \file
 * \brief Vector implementation
 */
#include <LinearAlgebra/vector.h>

#include <assert.h>
#include <math.h>
#include <stdlib.h>

struct VEC_Vector * VEC_alloc(
    const int length)
{
    struct VEC_Vector *const vector = calloc(1, sizeof(*vector));

    vector->data = calloc((size_t)length, sizeof(*vector->data));
    vector->length = length;

    return vector;
}

void VEC_free(
    struct VEC_Vector *const vector)
{
    free(vector->data);
    free(vector);
}

void VEC_set_element(
    struct VEC_Vector *const vector,
    const int pos,
    const double value)
{
    assert(pos < vector->length); // LCOV_EXCL_LINE

    vector->data[pos] = value;
}

double VEC_get_element(
    const struct VEC_Vector *const vector,
    const int pos)
{
    assert(pos < vector->length); // LCOV_EXCL_LINE

    return vector->data[pos];
}

double VEC_norm(
    const struct VEC_Vector *const vector)
{
    double squared_sum = 0.0;

    for (int i = 0; i < vector->length; ++i)
    {
        const double element = VEC_get_element(vector, i);
        squared_sum += element * element;
    }

    return sqrt(squared_sum);
}

void VEC_normalize(
    struct VEC_Vector *const vector)
{
    const double norm = VEC_norm(vector);

    for (int i = 0; i < vector->length; ++i)
    {
        const double normalized_value = VEC_get_element(vector, i) / norm;
        VEC_set_element(vector, i, normalized_value);
    }
}

double VEC_dot_product(
    const struct VEC_Vector *const a,
    const struct VEC_Vector *const b)
{
    assert(a->length == b->length); // LCOV_EXCL_LINE

    double result = 0.0;

    for (int i = 0; i < a->length; ++i)
    {
        result += VEC_get_element(a, i) * VEC_get_element(b, i);
    }

    return result;
}
