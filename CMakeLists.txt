cmake_minimum_required(VERSION 3.16)

project(GameEngine VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} src/main.c)
