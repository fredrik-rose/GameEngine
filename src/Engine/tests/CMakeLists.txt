add_executable(CoordinateSystemTransformationsTests coordinate_system_transformations_tests.c)

target_link_libraries(CoordinateSystemTransformationsTests LINK_PUBLIC
    Base
    Engine
    LinearAlgebra
    TestFramework
)

add_test(NAME CoordinateSystemTransformationsTests COMMAND CommonTests)
