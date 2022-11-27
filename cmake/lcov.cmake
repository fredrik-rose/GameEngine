add_custom_command(OUTPUT _run_lcov_parser
    POST_BUILD
    COMMAND lcov --no-external --capture --rc lcov_branch_coverage=1 --directory ${CMAKE_SOURCE_DIR}/src
        --directory ${CMAKE_BINARY_DIR}/src --output-file ${CMAKE_BINARY_DIR}/unfiltered_coverage.info
    COMMAND lcov --rc lcov_branch_coverage=1 --remove ${CMAKE_BINARY_DIR}/unfiltered_coverage.info
        '*/tests/*' '*/TestFramework/*' --output-file ${CMAKE_BINARY_DIR}/coverage.info
    COMMAND genhtml --rc lcov_branch_coverage=1 --ignore-errors source ${CMAKE_BINARY_DIR}/coverage.info
        --output-directory lcov
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_custom_target(lcov DEPENDS _run_lcov_parser)
