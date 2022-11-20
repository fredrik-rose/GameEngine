add_subdirectory(Base)
add_subdirectory(LinearAlgebra)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC LinearAlgebra)
