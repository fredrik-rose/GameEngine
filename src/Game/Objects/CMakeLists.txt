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

add_subdirectory(tests)
