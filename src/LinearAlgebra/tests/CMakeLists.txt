add_executable(VectorTests vector_tests.c)

target_link_libraries(VectorTests LINK_PUBLIC
    Base
    LinearAlgebra
    TestFramework
)

add_test(NAME VectorTests COMMAND VectorTests)
