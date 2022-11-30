/**
 * \file
 * \brief Math interface
 */
#ifndef BASE_MATHFUNCTIONS_H
#define BASE_MATHFUNCTIONS_H

/**
 * \brief Clamps a value to a certain range
 *
 * \param[in] x Value to clamp
 * \param[in] min_value The minimum value
 * \param[in] max_value The maximum value
 *
 * \return Value in range [min_value, max_value]
 */
double MATH_clamp(
    double x,
    double min_value,
    double max_value);

#endif /* BASE_MATHFUNCTIONS_H */
