add_executable(CommonTests common_tests.c)

target_link_libraries(CommonTests LINK_PUBLIC
    TestFramework
)

add_test(NAME CommonTests COMMAND CommonTests)
