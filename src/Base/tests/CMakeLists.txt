add_executable(CommonTests common_tests.c)
add_executable(CoordinatesTests coordinates_tests.c)
add_executable(MathFunctionsTests math_functions_tests.c)

target_link_libraries(CommonTests LINK_PUBLIC
    TestFramework
)
target_link_libraries(CoordinatesTests LINK_PUBLIC
    Base
    TestFramework
)
target_link_libraries(MathFunctionsTests LINK_PUBLIC
    Base
    TestFramework
)


add_test(NAME CommonTests COMMAND CommonTests)
add_test(NAME CoordinatesTests COMMAND CoordinatesTests)
add_test(NAME MathFunctionsTests COMMAND MathFunctionsTests)
