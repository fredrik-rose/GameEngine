add_library(Base
    coordinates.c
    math_functions.c
)

target_link_libraries(Base LINK_PRIVATE m)

target_include_directories(Base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
