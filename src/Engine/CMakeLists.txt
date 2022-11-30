add_library(Engine
    camera.c
    coordinate_system_transformations.c
    frame_synchronizer.c
    illumination.c
    renderer.c
)

target_link_libraries(Engine PRIVATE
    m
    LinearAlgebra
)

target_link_libraries(Engine PUBLIC
    Base
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
