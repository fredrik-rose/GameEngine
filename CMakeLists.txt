cmake_minimum_required(VERSION 3.16)

project(GameEngine VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

find_program(CMAKE_C_CPPCHECK NAMES cppcheck)
if (CMAKE_C_CPPCHECK)
    list(
        APPEND CMAKE_C_CPPCHECK
            "--enable=warning"
            "--inconclusive"
            "--force"
            "--inline-suppr"
            "--error-exitcode=-1"
    )
endif()

set(CMAKE_C_CLANG_TIDY clang-tidy -checks=*,-llvm-header-guard,readability-* -warnings-as-errors=* -header-filter=.)

add_executable(${PROJECT_NAME} src/main.c)

add_subdirectory(src)

find_package(Doxygen REQUIRED doxygen dot)
set(DOXYGEN_DISTRIBUTE_GROUP_DOC YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN_EXTRACT_PACKAGE YES)
set(DOXYGEN_EXTRACT_STATIC YES)
set(DOXYGEN_EXTRACT_ANON_NSPACES YES)
set(DOXYGEN_WARN_NO_PARAMDOC YES)
set(DOXYGEN_EXCLUDE "LICENSE.txt")
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_INLINE_SOURCES YES)
set(DOXYGEN_REFERENCED_BY_RELATION YES)
set(DOXYGEN_REFERENCES_RELATION YES)
set(DOXYGEN_REFERENCES_LINK_SOURCE NO)
set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_CALLER_GRAPH YES)
doxygen_add_docs(doc)
