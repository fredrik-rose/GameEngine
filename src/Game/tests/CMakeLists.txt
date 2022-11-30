add_executable(GameTests game_tests.c)

target_link_libraries(GameTests PRIVATE
    Base
    Game
    TestFramework
)

add_test(NAME GameTests COMMAND GameTests)
