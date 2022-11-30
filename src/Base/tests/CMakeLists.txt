add_executable(CommonTests common_tests.c)
add_executable(CoordinatesTests coordinates_tests.c)
add_executable(MathFunctionsTests math_functions_tests.c)

target_link_libraries(CommonTests PRIVATE
    Base
    TestFramework
)
target_link_libraries(CoordinatesTests PRIVATE
    Base
    TestFramework
)
target_link_libraries(MathFunctionsTests PRIVATE
    Base
    TestFramework
)

add_test(NAME CommonTests COMMAND CommonTests)
add_test(NAME CoordinatesTests COMMAND CoordinatesTests)
add_test(NAME MathFunctionsTests COMMAND MathFunctionsTests)
