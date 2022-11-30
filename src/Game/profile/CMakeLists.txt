add_executable(GameProfiler game_profiler.c)

target_link_libraries(GameProfiler PRIVATE
    Base
    Game
)
