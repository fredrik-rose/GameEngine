add_library(Engine
    camera.c
    coordinate_system_transformations.c
    renderer.c
)

target_link_libraries(Engine LINK_PRIVATE m)

target_link_libraries(Engine LINK_PUBLIC
    Base
    LinearAlgebra
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
