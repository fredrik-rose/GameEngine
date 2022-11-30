add_executable(SphereTests sphere_tests.c)
add_executable(TorusTests torus_tests.c)

target_link_libraries(SphereTests PRIVATE
    Base
    Engine
    LinearAlgebra
    Objects
    TestFramework
)
target_link_libraries(TorusTests PRIVATE
    Base
    Engine
    LinearAlgebra
    Objects
    TestFramework
)

add_test(NAME SphereTests COMMAND SphereTests)
add_test(NAME TorusTests COMMAND TorusTests)
