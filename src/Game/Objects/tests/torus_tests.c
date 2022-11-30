#include "../torus.h"

#include <Base/common.h>
#include <Base/coordinates.h>
#include <Engine/object.h>
#include <LinearAlgebra/vector.h>
#include <TestFramework/test_framework.h>

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_torus(void)
{
    /* NOTE: Assumes that the torus is created in a certain orientation. */
    const double inner_radius = 0.2;
    const double outer_radius = 0.6;
    struct OBJ_Object *const torus = TORUS_create(inner_radius, outer_radius);
    const double max_radius = outer_radius + inner_radius;
    const double min_radius = outer_radius - inner_radius;

    for (int i = 0; i < torus->length; ++i)
    {
        const struct COORD_Coordinate3D *const coordinate = &torus->coordinates[i];

        double vector_data[] = {coordinate->x, 0.0, coordinate->z};
        const struct VEC_Vector vector = {
            .length = LENGTH(vector_data),
            .data = vector_data
        };
        const double norm = VEC_norm(&vector);

        const int valid_x_z = ((min_radius - granularity) <= norm) && (norm <= (max_radius + granularity));
        const int valid_y =
            ((-inner_radius - granularity) <= coordinate->y) && (coordinate->y <= (inner_radius + granularity));

        TF_assert(valid_x_z);
        TF_assert(valid_y);
    }

    TORUS_free(torus);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_torus,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
