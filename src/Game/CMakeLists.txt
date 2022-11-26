add_library(Game
    game.c
)

target_link_libraries(Game LINK_PRIVATE m)

target_link_libraries(Game LINK_PUBLIC
    Base
    Engine
    Objects
)

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Objects)
