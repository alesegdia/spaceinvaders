cmake_minimum_required(VERSION 2.8.11)

project(spaceinvaders)

set(AETHER_USE_SDL 1)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(module/aether)
add_subdirectory(module/secs)

include("module/aether/cmake/Build.cmake")

file(GLOB_RECURSE GAME_SOURCES src/*.h src/*.cpp src/**/*.cpp src/**/*.h)
file(GLOB_RECURSE HADRON_SOURCES module/hadron/src/lib/**/*.h module/hadron/src/lib/**/*.cpp)

set(ALL_SOURCES ${GAME_SOURCES} ${HADRON_SOURCES})

ADD_AETHER_TARGET(spaceinvaders "${ALL_SOURCES}")

target_link_libraries(spaceinvaders secs)
target_include_directories(spaceinvaders PUBLIC module/secs/src/lib)
target_include_directories(spaceinvaders PUBLIC module/hadron/src/lib/)

set_property(TARGET spaceinvaders PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
