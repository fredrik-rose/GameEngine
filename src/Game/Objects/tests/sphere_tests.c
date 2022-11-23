#include "../sphere.h"

#include "Base/common.h"
#include "Base/coordinates.h"
#include "Engine/object.h"
#include "LinearAlgebra/vector.h"
#include "TestFramework/test_framework.h"

int TF_test_case_status;

static const double granularity = 1e-5;

static void test_sphere(void)
{
    const double radius = 2.0;
    struct OBJ_Object *const sphere = SPHERE_create(radius);

    for (int i = 0; i < sphere->length; ++i)
    {
        const struct COORD_Coordinate3D *const coordinate = &sphere->coordinates[i];
        double vector_data[] = {coordinate->x, coordinate->y, coordinate->z};
        const struct VEC_Vector vector = {
            .length = LENGTH(vector_data),
            .data = vector_data
        };
        const double norm = VEC_norm(&vector);

        TF_assert_double_eq(norm, radius, granularity);
    }

    SPHERE_free(sphere);
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    TF_test_case test_cases[] = {
        test_sphere,
    };

    return TF_run_suite(test_cases, LENGTH(test_cases));
}
