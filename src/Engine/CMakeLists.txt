add_library(Engine
    camera.c
)

target_link_libraries(Engine LINK_PUBLIC
    Base
    LinearAlgebra
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
