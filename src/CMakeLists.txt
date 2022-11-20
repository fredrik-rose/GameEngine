add_subdirectory(Base)
add_subdirectory(LinearAlgebra)
add_subdirectory(TestFramework)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Base LinearAlgebra)
