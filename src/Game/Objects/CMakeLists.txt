add_library(Objects
    sphere.c
    torus.c
)

target_link_libraries(Objects PRIVATE
    m
    Base
    Engine
    LinearAlgebra
)

target_include_directories(Objects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
