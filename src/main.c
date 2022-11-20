 #include "LinearAlgebra/vector.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    const struct VEC_Vector vector = {
        .length = 4,
        .data = calloc(4, sizeof(*vector.data))
    };

    const double element = VEC_get_element(&vector, 0);

    printf("Vector element: %lf\n", element);
}
