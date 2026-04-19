cmake_minimum_required(VERSION 3.25.0)

set(ENGINE_PROJECT_NAME core)
message("Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")
project(${ENGINE_PROJECT_NAME})

find_package(AgilitySDK REQUIRED)
include_directories(${PROJECT_SRC_DIR})
include_directories(${AgilitySdk_Include})

add_subdirectory(common)
add_subdirectory(cpu_renderer)
add_subdirectory(graphics)
add_subdirectory(maths)

add_library(${ENGINE_PROJECT_NAME} INTERFACE)
target_link_libraries(${ENGINE_PROJECT_NAME} INTERFACE common cpu_renderer graphics maths)

set_target_properties(${ENGINE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")
message("End Processing ${ENGINE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")