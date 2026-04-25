cmake_minimum_required(VERSION 3.25.0)

set(CORE_PROJECT_NAME graphics_common)
project(${CORE_PROJECT_NAME})
message("Processing ${CORE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")

set(CORE_GRAPHICS_COMMON_SOURCES
graphics_common.h
color.h
render_primitives.h
mesh_data.h
graphics_common.cc)

add_library(${CORE_PROJECT_NAME} STATIC ${CORE_GRAPHICS_COMMON_SOURCES})

target_link_libraries(${CORE_PROJECT_NAME} PUBLIC common maths)

set_target_properties(${CORE_PROJECT_NAME}
    PROPERTIES
    FOLDER "Core"
    VS_SOLUTION_FOLDER "Core")

message("End Processing ${CORE_PROJECT_NAME} - ${CMAKE_CURRENT_LIST_DIR}")
