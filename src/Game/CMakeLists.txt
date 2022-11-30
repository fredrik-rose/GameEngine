add_library(Game
    game.c
)

target_link_libraries(Game PRIVATE
    m
    Base
    Engine
    Objects
)

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Objects)
add_subdirectory(profile)
add_subdirectory(tests)
