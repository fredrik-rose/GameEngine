add_library(Objects
    sphere.c
)

target_link_libraries(Objects LINK_PRIVATE m)

target_link_libraries(Objects LINK_PUBLIC
    Base
    Engine
)

target_include_directories(Objects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
