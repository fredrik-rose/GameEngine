add_library(LinearAlgebra
    matrix.c
    vector.c
)

target_link_libraries(LinearAlgebra LINK_PRIVATE m)

target_include_directories(LinearAlgebra PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
