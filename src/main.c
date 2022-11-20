 #include "LinearAlgebra/matrix.h"
 #include "LinearAlgebra/vector.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    const struct VEC_Vector vector = {
        .length = 4,
        .data = calloc(4, sizeof(*vector.data))
    };

    const double vector_element = VEC_get_element(&vector, 0);

    printf("Vector element: %lf\n", vector_element);

    const struct MAT_Matrix matrix = {
        .rows = 4,
        .cols = 4,
        .data = calloc(4 * 4, sizeof(*matrix.data))
    };

    const double matrix_element = MAT_get_element(&matrix, 0, 0);

    printf("Matrix element: %lf\n", matrix_element);
}
