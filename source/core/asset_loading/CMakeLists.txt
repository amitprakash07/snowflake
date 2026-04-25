cmake_minimum_required(VERSION 3.25.0)

set(CORE_PROJECT_NAME asset_loading)
project(${CORE_PROJECT_NAME})
message("Processing ${CORE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")

set(CORE_ASSET_LOADING_SOURCES
obj_loader.h
obj_loader.cc)

add_library(${CORE_PROJECT_NAME} ${CORE_ASSET_LOADING_SOURCES})

target_include_directories(${CORE_PROJECT_NAME} PRIVATE ${PROJECT_EXTERNAL_SOURCE_DIR}/tinyobjloader/)

set_target_properties(${CORE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")

message("End Processing ${CORE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")
