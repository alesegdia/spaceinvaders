cmake_minimum_required(VERSION 2.8.11)

project(spaceinvaders)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(module/aether)

include("module/aether/cmake/Build.cmake")

file(GLOB_RECURSE GAME_SOURCES src/main.cpp rc/**/*.cpp src/**/*.h)

ADD_AETHER_TARGET(spaceinvaders "${GAME_SOURCES}")
