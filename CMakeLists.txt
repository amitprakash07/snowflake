cmake_minimum_required(VERSION 3.21.7)

include(${CMAKE_SOURCE_DIR}/cmake_modules/defs.cmake)
include(${PROJECT_CMAKE_MODULE_DIR}/common.cmake)

project(${PROJECT_NAME} LANGUAGES C CXX)
message("${PROJECT_INTERMEDIATE_DIR}")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/core ${PROJECT_INTERMEDIATE_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tools ${PROJECT_INTERMEDIATE_DIR}/tools)