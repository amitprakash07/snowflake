cmake_minimum_required(VERSION 3.21.7)

set(PROJECT_GIT_REPO_NAME "Snowflake")
set(PROJECT_NAME ${PROJECT_GIT_REPO_NAME})

project(${PROJECT_NAME} LANGUAGES C CXX)
message("Generating project files in ${PROJECT_BINARY_DIR}")

include(${CMAKE_SOURCE_DIR}/cmake_modules/defs.cmake)
include(${PROJECT_CMAKE_MODULE_DIR}/common.cmake)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/core ${PROJECT_INTERMEDIATE_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tools ${PROJECT_INTERMEDIATE_DIR}/tools)