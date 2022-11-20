add_library(TestFramework test_framework.c)

target_link_libraries(TestFramework LINK_PRIVATE m)

target_include_directories(TestFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
