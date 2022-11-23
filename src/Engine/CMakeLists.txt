add_library(Engine INTERFACE)

target_link_libraries(Engine INTERFACE
    Base
)

target_include_directories(Engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
