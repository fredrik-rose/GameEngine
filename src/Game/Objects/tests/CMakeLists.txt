add_executable(SphereTests sphere_tests.c)

target_link_libraries(SphereTests LINK_PUBLIC
    Base
    Engine
    LinearAlgebra
    Objects
    TestFramework
)

add_test(NAME SphereTests COMMAND SphereTests)
