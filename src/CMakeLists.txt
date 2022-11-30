add_subdirectory(Base)
add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(LinearAlgebra)
add_subdirectory(TestFramework)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Base
    Game
)
