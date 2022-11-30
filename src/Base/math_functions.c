/**
 * \file
 * \brief Math implementation
 */
#include <Base/math_functions.h>

#include <math.h>

double MATH_clamp(
    const double x,
    const double min_value,
    const double max_value)
{
    return fmax(fmin(x, max_value), min_value);
}
