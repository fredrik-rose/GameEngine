add_executable(MatrixTests matrix_tests.c)
add_executable(VectorTests vector_tests.c)

target_link_libraries(MatrixTests LINK_PUBLIC
    Base
    LinearAlgebra
    TestFramework
)
target_link_libraries(VectorTests LINK_PUBLIC
    Base
    LinearAlgebra
    TestFramework
)

add_test(NAME MatrixTests COMMAND MatrixTests)
add_test(NAME VectorTests COMMAND VectorTests)

