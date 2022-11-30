add_library(LinearAlgebra
    matrix.c
    vector.c
)

target_link_libraries(LinearAlgebra PRIVATE
    m
)

target_include_directories(LinearAlgebra PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
